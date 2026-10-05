# Cache de texturas GX — 2026-10-03

## Problema e mudança

O consumidor nativo `GXLoadTexObj` decodificava e criava uma textura Direct3D a cada carregamento. Na medição controlada de 180 frames originais Mario CPU versus Link CPU em Battlefield, isso gerou 37.415 uploads. O custo médio das chamadas de upload foi 292,528 ms por frame; o render consumiu 709,223 ms. Os tempos são de CPU, incluindo esperas, não consultas de tempo da GPU.

O cache em `src/gx_texture_cache.inc` conserva imagens decodificadas. A chave inclui dimensões, formato, quantidade de mipmaps e conteúdo real dos pixels e da paleta. Não usa apenas o endereço ou a identidade de um `GXTexObj` temporário. Wrap, filtros, LOD, bias e anisotropia são aplicados a cada binding, mesmo quando a imagem é reutilizada.

`GXInvalidateTexAll` continua conferindo a imagem original de cada unidade e atualiza a textura quando os bytes mudam. `GXLoadTlut` também confere o conteúdo das paletas. Nenhuma animação, callback HSD, triângulo ou atualização da simulação foi suprimida.

Há um limite de 256 entradas e orçamento de 32 MiB para backing de texturas contabilizado, snapshots de pixels e paletas. O overhead dos objetos Direct3D/vetores e padding de texturas lineares não está incluído nesse orçamento. Ao atingir o limite, novos recursos seguem o caminho anterior. Recursos retidos só são liberados ao desmontar o GX; não se invalidam referências temporariamente salvas pelos probes. Texturas mip físicas continuam sendo liberadas pelo caminho próprio existente.

## Medição reproduzível

`gx-profile.flag` habilita contadores no combate original. São registrados a cada 60 frames: lógica, render, apresentação, tempo de uploads, cópias EFB, primitivas, triângulos de early-Z, uploads e hits. O tempo de upload é parte do render e não deve ser somado novamente. Sem essa flag, não há consultas de relógio por upload/cópia nem escrita de logs de perfil por frame.

`verify-original-bootstrap.ps1 -Match -Performance -TimeoutSeconds 300` verifica 180 frames apresentados e salva o log de perfil separado do teste funcional de 900 frames. Não habilite `original-render-capture.flag` durante a medição. A comparação executa baseline e cache sequencialmente, com a mesma configuração do Xenia, sem compilação concorrente. `diagnostics/compare_gx_performance.py` compara os tempos e os samples completos da simulação.

Os arquivos `logs/gx-perf-baseline-controlled.txt`, `logs/gx-perf-optimized-controlled.txt` e `logs/gx-cache-performance-comparison.json` registram a comparação. Essa medição cobre a partida de diagnóstico no Xenia; não comprova o ganho nos menus ou no console real. As cópias EFB ainda fazem readback e sincronização e o grande número de primitivas continua um alvo para trabalho posterior. O áudio AX e as diferenças de material não foram resolvidos por este cache.

## Resultado controlado

| Medida média / 180 frames | Antes | Cache |
|---|---:|---:|
| Tempo total por frame | 713,270 ms | 523,038 ms |
| Render | 709,223 ms | 518,452 ms |
| Chamadas de upload, incluindo hits | 292,528 ms | 101,383 ms |
| Uploads efetivos | 37.415 | 1.938 |
| Primitivas submetidas | 203.241 | 203.241 |

O tempo por frame caiu 26,67%; os uploads caíram 94,82%. Os samples completos de ambos os CPUs são idênticos. A taxa estimada pelos tempos ficou em 1,40 versus 1,91 FPS nesse teste headless. Continua inadequada para jogar. Houve 35.477 hits; o limite de entradas e os recursos novos/dinâmicos ainda deixam uploads sem cache.

As capturas não são idênticas: no frame 60, superfícies antes brancas passaram a apresentar texturas depois da retenção dos recursos. A geometria/pose aparenta a mesma nas imagens inspecionadas. Isso é evidência visual de melhoria nesse frame, não prova de fidelidade integral nem diagnóstico definitivo da causa anterior. A simulação é comparada separadamente. Veja `logs/gx-cache-baseline-frame0060.png` e `logs/gx-cache-original-match-0060.png`.

## Ajustes da verificação

O combate com cache completou 900 frames apresentados e todos os samples CPU coincidiram com a revisão anterior. Na regressão de Training, o probe DVD encontrou um buffer local com alinhamento de 16 bytes, embora declarado com alinhamento de 32. A API DVD rejeitou a leitura corretamente. O probe passou a reservar 63 bytes e alinhar explicitamente uma janela de 32 dentro deles. A regra da API não foi relaxada; o probe passou após recompilar.

O teste completo de menus excedeu seu limite inicial de 90 segundos enquanto reproduzia um vídeo do arquivo, sem assert. `verify-xenia.ps1` recebeu um parâmetro opcional `TimeoutSeconds`; os critérios de aprovação permanecem iguais e os limites padrão foram preservados. A repetição usa 300 segundos. O log da tentativa inicial está em `logs/gx-cache-menu-timeout90.log`.

A comparação controlada de desempenho foi feita antes do ajuste do probe DVD, em `work/gx-profile-optimized.xex`. Esse ajuste não modifica o código de cache nem a partida, mas a imagem final é validada separadamente. O manifesto do pacote registra os hashes das imagens comparadas e da XEX final.

## XEX final

Depois de corrigir o alinhamento do probe DVD, a build final passou em Training (incluindo os probes GPU GX), no fluxo completo de menus com os vídeos de arquivo e retorno ao título, e novamente em 900 frames do combate original. Os 16 samples de cada bot coincidem integralmente com a revisão anterior. Sete capturas internas/finais foram salvas, com texturas nas plataformas nos frames inspecionados 60, 300 e 600.

A imagem retail publicada corresponde à XEX final testada. Hash, backup, imagens da comparação e logs estão em `logs/gx-cache-package-verification.json`. O launcher `start-original-match-xenia.ps1` usa o pacote atualizado. O pacote não contém flags de diagnóstico e a base original continua intacta.
