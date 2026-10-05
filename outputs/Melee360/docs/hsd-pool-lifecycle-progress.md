# Ciclo original de pools HSD

Foi adicionado um probe isolado sobre o allocator original objalloc.c. Ele registra um pool, aloca um objeto, libera o objeto e executa _HSD_ObjAllocForgetMemory. Comprova que used=0 e registry=NULL nao liberam a pagina HSD. O teste libera somente a pagina que ele mesmo criou e restaura o registry e obj_heap anteriores. Nenhum pool do runtime e descartado.

## Validacao

Build XDK aprovada: logs/hsd-pool-lifecycle-build.txt.
Xenia TrainingPreview aprovado: logs/hsd-pool-lifecycle-xenia.txt. O log exige o novo probe e verifica CSS, selecao de mapas, rejeicao de outro mapa, preparacao das regras Battlefield, cancelamento e retorno ao menu. Nao inicia gameplay. A reexecucao da build anterior tambem passou (logs/hsd-training-recheck.txt); o timeout anterior nao foi reproduzido, e nao foi demonstrada sua causa.
Auditoria Mario/Link: 112 simbolos ausentes, zero duplicatas; nao liga nem executa Fighter_Create.
A XEX validada foi copiada para package/RGH/Melee360/default.xex. Esta revisao foi testada no Xenia, nao no console real.

## Bloqueio para HSD_CreateMainHeap

A rotina original esquece classes, reinicializa pools, executa seis callbacks e destroi o heap inteiro. A protecao de alocacoes vivas detecta tambem paginas com todos os objetos livres; nao se pode exigir zero alocacoes e supor que HSD_ObjFree libere paginas. Antes de permitir destruicao e necessario comprovar que nao ha consumidores vivos, incluindo classes, GObjs e assets, e tratar o descarte em conjunto. O probe adicionado caracteriza esse contrato; nao implementa HSD_CreateMainHeap, nao adiciona stubs e nao altera os callbacks originais.
