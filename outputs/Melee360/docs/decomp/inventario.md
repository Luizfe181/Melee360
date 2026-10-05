# Inventário reproduzível

Snapshot: `17697c2d7e46f023f8c7320b75d8cf254ed8e5a4`. Gerado em 2026-10-02. Escopo: fontes/header/assembly presentes no checkout, incluindo SDK/CRT/TRK; não mede tamanho do binário nem porcentagem de decomp concluído.

2419 arquivos, 608026 linhas. Índice heurístico: 23672 definições aparentes. Regex não é parser C: macros, condicionais, comentários e assembly podem afetar os resultados; não é inventário certificado de funções executáveis. Marcadores asm/NON_MATCHING também não quantificam completude. Includes medem acoplamento textual, não grafo de chamadas nem dependências dinâmicas.

Inventário antigo de compilação: 987 entradas, 986 marcadas como compiladas. Esse inventário descreve o último ensaio registrado; não prova que os objetos foram recompilados após cada mudança de headers nem executados. Auditoria mais recente: 113 símbolos ausentes.

| Área | Arquivos | Linhas | Marcadores asm |
|---|---:|---:|---:|
| `libs/doldecomp` | 3 | 392 | 0 |
| `libs/dolphin` | 276 | 63814 | 204 |
| `src/MSL` | 45 | 3720 | 0 |
| `src/MetroTRK` | 54 | 5083 | 0 |
| `src/Runtime` | 14 | 1289 | 2 |
| `src/melee/cm` | 6 | 5208 | 0 |
| `src/melee/db` | 14 | 2394 | 0 |
| `src/melee/ef` | 13 | 4517 | 0 |
| `src/melee/ft` | 917 | 164292 | 0 |
| `src/melee/gm` | 167 | 58490 | 4 |
| `src/melee/gr` | 157 | 60999 | 5 |
| `src/melee/if` | 38 | 10195 | 0 |
| `src/melee/it` | 378 | 85290 | 1 |
| `src/melee/lb` | 68 | 19613 | 1 |
| `src/melee/mn` | 54 | 34130 | 0 |
| `src/melee/mp` | 8 | 12986 | 0 |
| `src/melee/pl` | 18 | 7158 | 0 |
| `src/melee/sc` | 2 | 55 | 0 |
| `src/melee/sfx` | 4 | 529 | 0 |
| `src/melee/ty` | 11 | 12489 | 0 |
| `src/melee/vi` | 26 | 2605 | 0 |
| `src/sysdolphin` | 145 | 52765 | 69 |
| `tools/dat-cli` | 1 | 13 | 0 |

Dados completos: [CSV](source-inventory.csv), [JSON por arquivo](source-inventory.json), [índice heurístico de funções](function-index.json), [métricas e includes](analysis-metrics.json).

Regeneracao do inventario lexical: diagnostics/analyze_decomp.py. As paginas de analise semantica e catalogos sao snapshots desta revisao; devem ser revisados quando o codigo mudar.
