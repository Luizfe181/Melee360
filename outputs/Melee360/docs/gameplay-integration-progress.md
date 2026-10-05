> Registro histórico da revisão anterior. Para os números e a XEX atuais, veja [runtime-dependency-progress.md](runtime-dependency-progress.md).

# Integração de gameplay e seleção — 2026-10-01

## O que mudou

`compile-gameplay.ps1` compila individualmente, com o compilador PowerPC do XDK, todos os 886 arquivos C nas áreas ft, gm, mn, gr, it, mp, pl, cm, if, ef, lb e sfx. Inclui a seleção original completa (`mncharsel.c`), lutadores e movimentos, lógica de partidas, cenários, itens, colisão, jogadores, câmera, interface e efeitos. O checkout original permanece intacto. Quando necessário, uma cópia gerada em `build/gameplay-objects/adapted` recebe as adaptações de declarações/literais descritas abaixo. O inventário registra caminho original, SHA256, fonte compilado, resultado e erros de cada unidade. A opção `-RetryFailed` repete somente as unidades ainda bloqueadas; sem essa opção, recompila tudo.

`collect-gameplay-dependencies.ps1` reúne somente os objetos aprovados em `build/gameplay-objects/original-gameplay-partial.lib` e lista os símbolos externos que a própria biblioteca não fornece. **Essa biblioteca de diagnóstico não está ligada à XEX.** Compilar um arquivo não demonstra correção do seu comportamento, de todas as estruturas ou das funções de plataforma que ele chama. Também não demonstra que todos os módulos do jogo estejam presentes nessa biblioteca.

O projeto Visual Studio também oferece os targets explícitos `CompileOriginalGameplay` e `AuditOriginalGameplayLink`. O build padrão da XEX continua separado. A auditoria grava o resultado negativo no JSON e termina normalmente para permitir inspecionar o relatório; consulte `linked`, não apenas o exit code do script.
Esses targets usam PowerShell 7, encontrado no runtime local do Codex quando disponível; `GameplayPowerShell` permite indicar outro executável instalado. Não alteram a política de execução do Windows PowerShell.

## Resultado verificado

| Conjunto | Arquivos compilados / total |
|---|---:|
| Lutadores e movimentos (`ft`) | 442 / 442 |
| Gerenciamento do jogo (`gm`) | 86 / 86 |
| Menus, incluindo seleção original (`mn`) | 26 / 26 |
| Cenários (`gr`) | 77 / 77 |
| Itens (`it`) | 183 / 183 |
| Colisão, jogadores, câmera, interface, efeitos, utilidades e efeitos sonoros | 72 / 72 |
| **Total deste alvo** | **886 / 886** |

Biblioteca gerada com sucesso: `original-gameplay-partial.lib`. Ela contém todos os objetos desse alvo, mas continua sendo parcial em relação ao jogo inteiro: não inclui o HSD completo, todos os demais subsistemas ou o SDK Dolphin. Uma unidade vazia do upstream (`ftCo_BuryWait`) produz aviso LNK4221; compilar essa unidade não fornece implementação de função ausente.

A biblioteca possui **1.090 símbolos externos** que ela própria não fornece, incluindo símbolos normalmente atendidos pelo CRT/XDK. A tentativa real de ligação com o CRT/XDK reduz isso a **745 símbolos ainda ausentes**, com **4.735 referências** a eles e **zero definições duplicadas**. O linker termina em LNK1120; não foi gerada uma XEX de gameplay. O target MSBuild de auditoria foi executado e confirmou esse resultado.

Também passaram a compilação Release/Compat do executável existente e as verificações XDK de ABI de Fighter. A base original continua com `git status --porcelain` vazio. A XEX distribuída permanece com SHA256 `ED5D9A85E27D9280FC9100768F86FF245695FAEFE1283578A55FBD6C4F0C2C3A`; não foi substituída por essa biblioteca ou pela auditoria.

Adaptações isoladas em `compat`, geradas a partir dos headers originais:

- Flags `MotionFlags`: expressões constantes em macros, mantendo o tipo e as expressões; o compilador C do XDK rejeitava inicializadores que usavam variáveis `const`.
- `Fighter.x594.x0.x596_bits`: os dois campos agora usam armazenamento `u16`, evitando a separação de unidades de bitfield feita pelo MSVC. Mantida a verificação original de tamanho. Antes: Fighter 0x23F0, input 0x624, mv 0x2344. Depois: 0x23EC, 0x620, 0x2340, respectivamente.
- `gameplay_boundary.h`: constantes matemáticas, classificação de ponto flutuante usando os serviços do CRT do XDK e declarações das APIs float originais. Os macros float do CRT colidiam com definições originais e variáveis locais chamadas `sin`/`cos`. Essas declarações não fornecem implementações ausentes. O clock depende do símbolo externo `Melee360OSBusClock`, que ainda exige um fornecedor de plataforma consistente com OSGetTime/OSGetTick.
- Cópias C geradas: flags locais constantes como macros; anotação de alinhamento movida do fim para o início da declaração, conforme a sintaxe MSVC; contagens constantes de arrays como enums; literal `3.4028235e38f` escrito com a representação precisa do maior float finito, pois o MSVC rejeitava a grafia arredondada. Não houve reescrita dos algoritmos de combate, física ou seleção.
- Mantida a tolerância `FLT_EPSILON` do projeto original após incluir os limites do CRT, evitando uma troca silenciosa pela definição padrão do XDK.

`tests/fighter_layout_xbox.c` verifica tamanho de Fighter, união x594 e offsets de x594/x598, posição, entrada, colisão, frame de animação e variáveis de movimento. Compilado com o XDK; as verificações falham na compilação se houver diferenças. Isso não é uma auditoria de todos os campos de todos os tipos.

Resultados completos: `logs/gameplay-compile/inventory.json`, `summary.json`, `external-dependencies.txt` e logs individuais. A compilação Release/Compat de regressão está em `logs/gameplay-core-regression-build.txt`.
Warnings de compilação ficam em `warnings.csv` e no resumo por código. Avisos de declaração implícita/conversão exigem revisão antes de executar os módulos; ausência de erros de compilação não substitui isso.
O levantamento final inclui 131 avisos C4013 (declarações implícitas), 67 C4028 (parâmetros inconsistentes), 20 C4715 e 19 C4716 (caminhos/funções sem retorno). São pendências reais de revisão do código e das fronteiras, mesmo com os 886 arquivos aceitos pelo compilador.

`audit-gameplay-link.ps1` tenta ligar diretamente todos os objetos com o CRT/XDK, sem eliminar funções não chamadas, sem `/FORCE` e sem stubs. É uma auditoria sem geração de XEX, com entry exclusivo de diagnóstico; não é uma partida nem um teste de comportamento. Erros completos em `link-audit.txt`, símbolos em `link-missing-symbols.txt` e resultado em `link-audit-summary.json`. O número de referências pode repetir o mesmo símbolo em várias funções; o número de símbolos únicos é o indicador relevante. Bibliotecas de outros subsistemas do decomp, o HSD completo, serviços de plataforma e partes não decompiladas continuam necessários.

## Estado da XEX

A XEX distribuída continua na versão funcional de menus/animações/modelos. Esta etapa não adiciona luta ou a máquina original completa da seleção à execução. A confirmação do personagem ainda é o fluxo de diagnóstico do port, sem iniciar a cena de partida. Os 25 modelos continuam em pose estática. Não foi feita uma nova validação de gameplay no console porque ainda não há gameplay executável.

## Progresso estimado do port completo

**Cerca de 20%, com faixa aproximada de 15–25%.** Estimativa de engenharia por funcionalidades, não medida automática, prazo ou porcentagem de arquivos copiados/compilados. Rubrica explícita para o alvo final jogável no Xbox 360 RGH/JTAG:

| Área | Peso no projeto | Conclusão estimada da área | Contribuição |
|---|---:|---:|---:|
| Boot, runtime, acesso aos assets e empacotamento | 10% | 80% | 8 pontos |
| Renderer HSD/GX e animações | 20% | 30% | 6 pontos |
| Menus e seleção completa | 15% | 40% | 6 pontos |
| Gameplay original, lutadores e modos | 30% | 0% em execução | 0 |
| Cenários, itens e integração de conteúdo | 10% | 0% em execução | 0 |
| Áudio | 5% | 0% | 0 |
| Saves e memory card | 5% | 10% | 0,5 ponto |
| Validação final no console, desempenho e estabilidade | 5% | 10% | 0,5 ponto |

Soma: 21 pontos, arredondada para aproximadamente 20%. Os avanços de compilação reduzem bloqueios técnicos; não aumentam por si sós a conclusão funcional do gameplay. Essa estimativa poderá ser revisada quando uma partida executar.

## Próximos bloqueios concretos

1. Resolver as referências externas documentadas, incluindo módulos HSD fora desse alvo, funções não decompiladas e serviços Dolphin/GX/OS/AX. Depois repetir a ligação e as verificações de ABI; nenhum símbolo ausente deve ser ocultado com stubs para declarar gameplay funcional.
2. Integrar o ciclo original GObj/JObj, scene manager, preload e allocators necessários a `mnCharSel_Scene_OnEnter/OnFrame/OnExit`; as pontes atuais de menu não executam esse ciclo completo.
3. Ligar a seleção à inicialização real de partida/jogadores, estados de lutadores, dados comuns e de cada personagem. Validar layouts e bitfields antes de usar dados binários originais.
4. Integrar animações de lutadores, colisões de cenário, física, câmera, hitboxes e eventos de uma primeira partida. A renderização atual de modelos não executa essas funções.
5. Completar o renderer necessário aos materiais, personagens e cenários e depois áudio, saves, modos e validação no hardware.

Nenhuma função ausente de gameplay foi substituída por um retorno fictício para permitir chamar a partida. A biblioteca parcial é um artefato de preparação, não uma build completa do jogo.
