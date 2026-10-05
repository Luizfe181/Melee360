> Atualização posterior: cache de texturas GX e comparação de desempenho em [otimização de texturas](gx-texture-cache-performance.md). Este documento conserva as evidências da primeira revisão do renderer.

# Desenho original da partida — 2026-10-03

## Caminho integrado

O diagnóstico `original-match.flag` executa `gm_Scene_Vs_OnEnter`, os Fighters originais de Mario e Link e Battlefield. Cada atualização executa o scheduler e `gm_Scene_Vs_OnFrame`; depois chama `HSD_StartRender`, `HSD_GObj_80390FC0` e `HSD_Init_803755A8`. São as câmeras, JObjs, PObjs, animações e callbacks da partida original. Os modelos não vêm do visualizador de personagem nem de uma cena de gameplay substituta.

O GX nativo recebe esses comandos e desenha via Direct3D do XDK. Uma superfície EFB de 640×480 conserva as coordenadas usadas pelos assets e pelas sombras. Seu resolve é apresentado em 4:3 no backbuffer de 1280×720. O painel FPS/dano/posição continua separado do desenho original. O boot normal conserva os menus existentes; o combate ainda é aberto pelo launcher de diagnóstico.

## Incompatibilidades resolvidas

- Os remainders HSD agora usam `DEBUG=1`, como os demais módulos que chamam os consumidores GX. Antes, um `GXEnd` vazio deixava a instrumentação de primitive aberta. A tradução também reconhece que o FIFO termina pelo número de vértices, mesmo quando o original omite `GXEnd`.
- Normais S8/S16 usam as escalas fixas do GX. NBT/NBT3 conservam normal, binormal e tangente; matrizes de normal são exigidas quando utilizadas pela iluminação ou pelo emboss mapping.
- Coordenadas de textura inteiras, com sinal e fração, são decodificadas nas unidades correspondentes. Índices de matriz de textura por vértice são consumidos antes da posição.
- RGBX8, RGBA4 e RGBA6 receberam decodificação do formato compacto, incluindo tamanho correto nos display lists e arrays indexados.
- O quad original de fundo das sombras escreve doze floats XYZ em seis chamadas `GXPosition2f32`. O consumidor passou a tratar essa sequência como um fluxo de escalares.
- A cópia `GX_CTF_R4` usada pelo HSD Shadow grava o canal vermelho em tiles de 8×8, com dois pixels por byte. Isto não habilita automaticamente todos os formatos de cópia ou o downsampling.
- As escritas físicas `GXWGFifo.u8/f32` de `psdisp.c` são convertidas em chamadas de um consumidor FIFO nativo. A geometria, ordenação e cálculos das partículas permanecem originais. A cópia gerada substitui o módulo correspondente na biblioteca de dependências.
- Texgens BUMP0–7 usam a luz selecionada, os vetores NBT transformados e a coordenada anterior. A fórmula foi conferida na [implementação de referência do Dolphin](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/VertexShaderGen.cpp).
- Quando todos os 256 valores possíveis de alfa passam e não há Z texture, o teste de profundidade nativo produz o mesmo resultado sem a emulação por triângulo. Os casos com descarte continuam no caminho anterior.

`GXSetTevClampMode` é uma entrada obsoleta: o SDK original não escreve registradores nessa função e só aborta em DEBUG. Foi conservada a semântica do SDK release para essa entrada, sem inventar uma operação de clamp. O corpo original e sua procedência estão em `logs/original-tev-provenance.json`. Os demais asserts continuam ativos. Não foram acrescentados stubs para funções ausentes nem `/FORCE`.

## Evidência e limites

O primeiro teste com desenho completou 900 frames apresentados no Xenia, sem assert. Cada bot apresentou 15 posições e 12 estados distintos, entradas CPU, estados no chão e no ar e dano: Mario 56,03%, Link 47,64%. As capturas internas dos frames 1, 60 e 300 mostram Battlefield, a entrada dos Fighters e os modelos em combate. A captura ocorre antes do overlay. A build final repetiu os 900 frames e salvou sete capturas: EFB nos frames 1, 60, 300 e 600, e backbuffer nos frames 1, 300 e 600. No log, capturas do backbuffer usam identificador 10000 + frame. A imagem do frame 600 confirma Mario com suas cores normais e Link; o Mario branco do frame 300 ocorre durante um estado de dano e não comprova isoladamente uma falha de material. As plataformas claras continuam uma diferença visual a investigar.

[Captura final do frame 600](../logs/original-match-presented-0600.png).

As verificações ficam em `logs/original-match-runtime.log`, `logs/original-match-logic-verification.json`, `logs/original-match-captures.json` e no manifesto `logs/original-render-package-verification.json`. A auditoria de dependências Mario/Link liga sem símbolos ausentes e sem duplicações; isso não prova a implementação de toda a API GX.

Ainda há diferenças visuais: superfícies muito claras, materiais/cores e fundo/HUD incompletos exigem comparação com o original. As capturas não comprovam fidelidade integral do TEV. O renderer completo também ficou lento no teste headless, aproximadamente 2–3 frames por segundo; não há afirmação de desempenho adequado no console. O áudio original AX ainda interrompe o DMA ao encontrar um modo de voz não suportado. A música e os testes de áudio dos menus são um caminho separado.

O cenário validado é Mario CPU nível 9 versus Link CPU nível 9, três stocks, Battlefield, sem itens aleatórios. Não valida todos os golpes, personagens, cenários, perdas de stock/respawn ou o encerramento de uma partida. Este launcher ainda não integra controle humano. A revisão foi testada no Xenia, não em hardware real.

## Reprodução

Execute `start-original-match-xenia.ps1` em PowerShell. O script cria uma cópia de execução própria em `work/xenia-match-play-*`, lê os assets por junction, habilita readback de resolve nessa configuração e remove a flag ao fechar o Xenia. Não altera a configuração instalada do emulador nem o save do jogador.

Para repetir o teste automatizado, prepare o XEX retail em `work/xenia-test/package`, habilite temporariamente `original-render-capture.flag` nessa cópia e execute `verify-original-bootstrap.ps1 -Match -TimeoutSeconds 600`. O marcador de aprovação vem depois do `Present` do frame 900. Execute `diagnostics/verify_original_match.py` para conferir a lógica. A flag de captura deve ser removida em `finally`.

A base `work/melee-base` permanece intacta. As adaptações estão em `src/gx_*`, `src/match_surface.inc`, `src/original_runtime_boot.c`, `src/main.cpp`, `src/fps_overlay.cpp`, nos geradores de remainders/procedência e nos scripts de compilação/verificação. O projeto XDK agora gera `default.map` para localizar chamadas durante os diagnósticos.

## Pacote final verificado

A XEX retail publicada corresponde byte a byte à imagem testada: SHA-256 EEBF2C56019A0976D5F0A51FBBFEE1F55EEE19349ED333DF522A71151745D97D. A imagem anterior foi preservada em backup; a base original segue sem alterações. O pacote não contém flags de diagnóstico.

A build final passou no combate original com 900 frames apresentados, no fluxo Training, na música/fluxo do menu e nas quatro variantes do diagnóstico Battlefield com a flag AA. Cada variante completou 120 atualizações animadas. Esse último teste não significa que a partida original utiliza todos os modos AA/entrelaçados. Os logs finais estão enumerados no manifesto do pacote.
