# Display lists: medição separada — 2026-10-04

## Decisão desta rodada

MANTER: gameplay, física, AI, HSD e emissão GX original; validação integral das display lists antes de qualquer draw; DrawPrimitiveUP e caminho de comparação existente.

ADAPTAR: diagnóstico detalhado GX, com contadores separados de chamadas, bytes, comandos e vértices, além de tempo de preflight e execução. Contadores reiniciados ao ativar o perfil. Apenas o perfil detalhado habilita os relógios e contadores novos.

MANTER A TRADUÇÃO: execução CPU das display lists com arrays e matrizes atuais; conversão de vértices, shaders, texturas e cópias existentes. Nenhum cache de geometria transformada foi introduzido.

## Como funciona / hipótese

GXCallDisplayList faz duas passagens: valida toda a lista e então executa os comandos. Antes, os tempos não separavam essas etapas. Medir primeiro evita remover segurança ou criar cache de listas sem benefício relevante. O experimento anterior com triangle strips nativos permanece rejeitado e preservado.

## Validação

Release/Compat compilou com sucesso; avisos C4214 existentes permanecem. Partida automática original Mario/Link em Battlefield no Xenia, áudio mute=true, 180 frames, sem compilação simultânea. Marcador final confirmado; nenhuma mensagem FAILED ou HSD ASSERT encontrada.

| Métrica cumulativa nos 180 frames | Resultado |
| --- | ---: |
| Chamadas de display list | 43.309 |
| Bytes processados | 31.529.056 |
| Comandos | 194.687 |
| Vértices de display lists | 4.552.476 |
| Preflight médio | 2,286 ms/frame |
| Execução média | 165,445 ms/frame |
| Render médio | 327,523 ms/frame |
| Lógica média | 3,864 ms/frame |
| Draws | 203.241 |
| Uploads | 1.367 |
| Cópias | 345 |

Tempos CPU de parede, incluindo esperas GPU. Execução contém processamento de vértices e draws; sobrepõe packet/submit/draw e não deve ser somada a esses tempos. Preflight equivale a cerca de 0,70% do render medido. Mesmo eliminá-lo integralmente teria alcance limitado; portanto não priorizar cache apenas da validação.

Ganho de performance: nenhum reivindicado; esta rodada mede o gargalo. Contagens de draws/uploads/cópias iguais ao baseline anterior, mas isso não é comparação controlada de velocidade ou equivalência visual. Não houve nova comparação de pixels nem teste de hardware nesta rodada. Probes completos anteriores não foram repetidos porque a alteração apenas instrumenta o caminho existente.

Próximo gargalo: execução por vértice dentro das display lists. Avaliar formatos e escalas invariantes por comando, helpers de atributos, iluminação/texgen e custo de emissão, preservando atualização de arrays/matrizes e saída. Geometria transformada não pode ser reutilizada somente pela identidade da lista.

## Arquivos

- src/gx_profile.inc: estrutura, reset e relatório separado.
- src/gx_display_list.inc: timers das duas passagens e contadores.
- docs/display-list-profile-20261004.md: registro desta rodada.
- logs/display-list-profile-build.txt: compilação.
- logs/display-list-profile-runtime.txt: partida e medições.

Pacote publicado preservado: SHA256 95074C0C2CFC7226F2ABE2E88CBB4975411A1A6FD35054DA0FAE079CCE210738. XEX de teste restaurado e flags temporárias removidas pelo verificador.