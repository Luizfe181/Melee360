# Troca de heap HSD — 2026-10-02

Implementado HSD_SetHeap com o allocator original OS: valida o heap e atualiza
tanto o heap HSD como __OSCurrHeap. A arena é inicializada uma única vez com
quatro descritores; 512 KiB dos 64 MiB ficam reservados para uma segunda região.
O inicializador HSD completo ainda não está integrado.

Cada HSD_MemAlloc acrescenta um cabeçalho privado alinhado de 32 bytes com o
heap proprietário. HSD_Free libera no heap de origem, mesmo após uma troca.
Isso preserva alocações dos menus; aumenta o custo por alocação em 32 bytes.
Não permite destruir/recriar um heap enquanto seus objetos continuam vivos:
HSD_CreateMainHeap e seus callbacks originais ainda precisam ser integrados.

O primeiro teste tentou criar uma região fora da arena e foi rejeitado pelo
assert original OSCreateHeap. Corrigido para uma região separada dentro da
arena registrada. Nenhuma restrição do allocator foi removida.

Build Release/Xbox 360/Compat passou. No Xenia, a troca entre dois heaps,
preservação de dados vivos, liberação pelo proprietário, restauração do heap
atual e retorno ao mesmo total de memória livre passaram. Também passaram os
probes anteriores e a navegação Training/CSS/seleção Battlefield. Log:
logs/hsd-heap-xenia.txt. Falta validação em console físico.

Auditoria Fighter: 150 símbolos ausentes, zero duplicatas; completa: 171,
354 referências, zero duplicatas. HSD_SetHeap saiu da lista por implementação
real. Não foi criado Fighter nem produzido frame de gameplay. GX do Mario,
TEV, áudio e restante do ciclo de inicialização permanecem pendentes.

A XEX em package/RGH/Melee360/default.xex contém essa mudança. A anterior foi
preservada em logs/default-before-hsd-heap-transition.xex. Base original intacta.
