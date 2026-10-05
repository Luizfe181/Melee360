# Reestruturação da camada GX — 5 de outubro de 2026

## Escopo autorizado e arquitetura

O usuário autorizou refazer somente a camada GX. Gameplay, física, AI, state machines, HSD e dados originais continuam preservados. API GX → tradução Melee360 → recursos nativos XDK é o contrato externo. Não substituir cenas por simulações nem trocar áudio/serviços como parte desta reestruturação.

Esta rodada entrega a primeira etapa, **uma fronteira privada de submissão nativa**, não a reescrita completa de GX, TEV, texturas e cópias. O backend anterior permanece selecionado quando gx-native-submit.flag está ausente.

## Antes da alteração

profileDraw em gx_direct.cpp chamava DrawPrimitiveUP diretamente. Preparação dos vértices, expansão das topologias, shaders, passes de alpha/early-Z, texturas e cópias estavam acoplados ao mesmo caminho. Há custo por vértice significativo, mas a submissão é apenas uma parcela desse custo. Não há promessa de que trocar a chamada D3D isoladamente resolva o FPS.

Classificação: ADAPTAR a fronteira de submissão; MANTER API/ordem e lógica HSD; MANTER A TRADUÇÃO de TEV, transforms, lighting, texgen, texturas e EFB/XFB até a etapa específica de cada uma.

## Implementação válida desta rodada

- gx_native_submit.h/.cpp expõem Open, Draw, Close e Report, sem exportar APIs novas para o jogo.
- O caminho opcional usa BeginVertices/EndVertices do XDK. Converte primitive count para vertex count com limites de overflow, copia o mesmo payload e finaliza antes de liberar o ponteiro temporário.
- O XDK é proprietário da memória de comandos e de seu lifetime. Não reter ponteiros retornados por BeginVertices.
- Nenhuma alteração na ordem de primitives/passes, topology, shaders, atributos, arrays GX ou matrizes.
- O antigo DrawPrimitiveUP fica atrás da mesma fronteira como referência. NoDraw e os timers existentes continuam funcionando.
- Contadores de bytes/draws e identificação do modo no log mostram que o caminho novo realmente foi ativado.

Não há ainda VB/IB persistente validado, nem eliminação da cópia CPU ou migração de iluminação/texgen para GPU. BeginVertices é uma API nativa gerenciada e não prova uma arquitetura interna diferente da implementação UP do próprio XDK.

## Experimento com buffers explícitos: bloqueio real

A primeira tentativa usou oito páginas VB de 1 MiB, append-only e fences na reutilização. No ensaio de combate executou 203241 draws sem fallback/espera registrada, mas mudou o conteúdo das cópias e o número de uploads. O probe de alpha confirmou falha: test=3 retornou zero pixels quando deveria desenhar.

Foram testados offset no stream, StartVertex, memória CPU-cached e lock normal. O probe continuou falhando. A causa precisa de diagnóstico de vertex fetch/coerência; nenhuma dessas hipóteses foi comprovada. Não atribuir a redução aparente de tempo desse renderer incorreto à otimização.

Código preservado em diagnostics/experiments/gx-native-ring-unvalidated.cpp; logs das falhas e performance inválida em logs/gx-native-submit. Esse código não faz parte do caminho ativo da versão final desta rodada.

## Migração para C:\melee360

Dois problemas impediram a referência antes de qualquer comparação válida:

1. Inventário de objetos com caminhos absolutos antigos impedia gerar gameplay.lib. audit-fighter-create.ps1 agora resolve o sufixo conhecido do projeto no diretório atual e valida cada arquivo ausente; não reescreve logs históricos/proveniência nem cria objetos substitutos.
2. work/xenia-test/package/data estava vazio. Foi substituído por junction para os assets já presentes no pacote, sem duplicação no SSD. Não apagar recursivamente esse vínculo como se fosse uma cópia de assets.

O test.toml teve seu log_file atualizado para o novo workspace, com backup. Isso é reparo de ambiente; não é mudança de gameplay. A base Git permanece limpa.

## Validação funcional concluída

- Release/Compat compilou no workspace novo. O primeiro erro de macro INVALID_FILE_ATTRIBUTES foi corrigido para a convenção DWORD usada pelo XDK.
- Auditoria da biblioteca original e link final passaram após resolver a migração.
- Training e probes existentes passaram no caminho XDK-managed: alpha, textura/paleta/mips/8 unidades, 32 cópias e demais verificações exigidas pelo verificador.
- Duas partidas de 180 frames com captura: referência e novo caminho. Capturas internas 640×480 dos frames 1 e 60 com **zero pixels diferentes**.
- Samples de Fighter nas capturas idênticos. Nenhum FAILED/HSD ASSERT no conjunto válido.
- Áudio de todos os testes silenciado. Nenhuma compilação ocorreu junto com as medições.

Limites: dois frames comparados, samples de CPU, uma configuração de Mario/Link Battlefield, nenhum hardware real nesta rodada. Não prova fidelidade de todos os frames/modos/personagens. Não houve combate longo de 900 frames para esta nova revisão.

## Próximas etapas da reestruturação

1. Separar estado GX e packet/vertex preparation da submissão, com snapshots e invalidação explícita. Preservar acesso a arrays/matrizes mutáveis.
2. Reestruturar iluminação e texgen com equivalência testada. Não alterar comportamento para ganhar FPS; estudar GPU somente depois de reproduzir os mesmos modos/ordens/rounding necessários.
3. Retomar VB/IB com um probe mínimo de vertex fetch, readback/query e lifetime; corrigir o bloqueio acima antes de promover buffers explícitos. Preservar caminho gerenciado/UP como referência.
4. Migrar textura/cache e ownership sem eviction de recursos emprestados ou GPU em voo.
5. Separar TEV/shaders e estado D3D, considerando UI/intro/probes e StateBlock, evitando caches de estado inválidos.
6. Reestruturar cópias EFB/XFB com coerência RAM/GPU, filtros e pixels originais antes de eliminar readbacks.
7. Regressões longas e console real antes de promover novo renderer como padrão.

## Arquivos alterados/criados

- src/gx_native_submit.h e .cpp: novo backend de submissão.
- src/gx_direct.cpp: integração Open/Draw/Close.
- src/gx_profile.inc: relatório do novo backend.
- Melee360.vcxproj: unidade nativa adicional.
- audit-fighter-create.ps1: resolução segura de objetos após mudança de diretório.
- diagnostics/run_gx_native_submit.ps1 e analyze_gx_native_submit.py: comparação antes/novo/depois.
- diagnostics/run_gx_native_regression.ps1 e analyze_gx_native_regression.py: probes/capturas.
- diagnostics/experiments/gx-native-ring-unvalidated.cpp: tentativa rejeitada para análise.
- docs/gx-rewrite-20261005.md: este registro.
- work/xenia-test/test.toml e junction data: ambiente de teste reparado.

Pacote publicado preservado (SHA256 95074C0C2CFC7226F2ABE2E88CBB4975411A1A6FD35054DA0FAE079CCE210738). A candidata requer a flag para ativar o caminho novo. Não declarar a camada GX toda refeita por existir este módulo.
## Resultado de desempenho do caminho validado

Mesma candidata, três partidas de 180 frames, referência → XDK-managed → referência, sem capturas:

| Métrica | Referência antes | Novo | Referência depois |
| --- | ---: | ---: | ---: |
| Render ms/frame | 326,616 | 315,874 | 336,392 |
| Draws | 203241 | 203241 | 203241 |
| Uploads | 1367 | 1367 | 1367 |
| Cópias | 345 | 345 | 345 |

Redução observada 3,289–6,099%, drift das referências 2,993%. Uma execução por condição; não há intervalos estatísticos e não extrapolar para FPS do console. Não é prova definitiva de ganho sustentado. Samples CPU iguais nas três execuções. Manter opcional; ampliação de duração/modos e repetições ainda necessária.

Evidências: logs/gx-native-submit/analysis.json e regression.json. Tempos CPU incluem esperas e estágios aninhados. O ensaio do ring inválido está isolado em ring-invalid-performance e não participa destes resultados.