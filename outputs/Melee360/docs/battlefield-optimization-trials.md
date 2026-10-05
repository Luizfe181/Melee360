# Ensaios de otimização de Battlefield — 2026-10-04

Foram testadas três alternativas isoladas em Xenia headless, com a mesma XEX por grupo, cache 64 MiB, 180 frames originais de Mario CPU contra Link CPU. Não foram reduzidos polígonos, resolução, IA, colisões ou animações. Referências foram executadas antes e depois dos candidatos. Não houve comparação com o console físico nem medição de desempenho de menus.

## Resultados

| Alternativa | Tempo de referência | Candidato | Referência repetida | Decisão |
|---|---:|---:|---:|---|
| Apenas constantes dos estágios TEV ativos | 346,050 ms | 354,086 ms | 348,516 ms | Rejeitado |
| Cópia de pixels especializada para filtro identidade | 346,050 ms | 345,985 ms | 348,516 ms | Ganho total inconclusivo; retirado |
| Cópia auxiliar somente de imagens paletizadas | 345,413 ms | 346,275 ms | 336,043 ms | Rejeitado |

O TEV ativo reduziu registros enviados de 39022272 para 12344625 (aproximadamente 68%) e o pipeline de 6,854 para 5,823 ms/frame, mas o frame completo piorou. A cópia identidade reduziu o tempo interno de cópia de 37,281 para 30,428 ms/frame, mas o frame completo quase não mudou contra a primeira referência (0,019%). A variação entre referências limita as conclusões de ganhos pequenos. Esses tempos parciais estão contidos no render; não devem ser somados novamente.

Todos os candidatos apresentaram as mesmas amostras CPU e contagens de desenho, uploads e cópias. Não foi realizada validação visual completa nem regressão de 900 frames dos candidatos, pois nenhum demonstrou ganho suficiente para adoção. A compilação Release/Compat dos candidatos passou. Eles foram retirados do caminho ativo e o código restaurado foi recompilado.

## Reprodução e evidências

`diagnostics/compare_gx_phase_candidates.py` analisa os logs e gera `logs/gx-phase-candidates-comparison.json`, com valores completos, comparação CPU e desenhos. Logs dos primeiros dois testes: `gx-phase-{baseline,active,copy,baseline-repeat}.txt`. Terceiro teste: `gx-snapshots-{baseline,optimized,baseline-repeat}.txt`.

As implementações não adotadas foram arquivadas em `diagnostics/experiments/gx-active-tev-rejected.inc`, `gx-copy-identity-unproven.inc` e `gx-palette-snapshots-rejected.cpp`. São snapshots de experimentos, não módulos do projeto. As flags temporárias foram removidas. A XEX de teste foi restaurada a partir da imagem publicada.

O pacote validado continua sendo a revisão de cache 64 MiB, SHA256 1E0458D94556D1F4B2FAE880929BEBAE29039A775F44B89670641466D4E238A6. Não foi publicada uma nova build nem reivindicado um ganho novo. A base decomp permanece intacta.

## Próxima medição necessária

O perfil atual agrega trabalho CPU e espera GPU. Separar transformação/montagem de vértices, submissão de comandos e esperas é necessário antes de atribuir o gargalo ao shader TEV ou às cópias. Alterações que reduzem comandos ou memória devem continuar sendo avaliadas pelo frame completo, não apenas pelos contadores internos.
