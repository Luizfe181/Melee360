# Arena e ownership HSD

Implementado HSD_GetNextArena com os limites reais da arena primária do port (64 MiB menos descritores/alinhamento e reserva de 512 KiB). A base original foi preservada.

HSD_MemAlloc/HSD_Free contabilizam alocações por heap e continuam liberando pelo proprietário gravado no header. A consulta de elegibilidade exige heap não corrente, zero alocações HSD e lista allocated vazia no allocator original OSAlloc. Heaps inválidos ou destruídos são recusados. Esta consulta não intercepta OSDestroyHeap nem executa a troca original automaticamente.

O generator do allocator expõe apenas uma consulta de sua lista real; o algoritmo original não foi substituído. Testes host verificam alocações diretas, isolamento, heap destruído/reutilização, alinhamento, coalescência e esgotamento. Os probes Xbox verificam preservação de buffers na troca de heap, contadores e limites da arena.

Build XDK: logs/hsd-arena-ownership-build.txt. Auditoria Mario/Link: logs/hsd-arena-ownership-audit.txt, 112 ausências, zero duplicatas, linked=false, executed=false. Validação Xenia: logs/hsd-arena-ownership-xenia.txt.

## Bloqueio real

HSD_CreateMainHeap original ainda não está integrado. Ele esquece classes, reinicializa pools e executa callbacks de descarte antes de destruir o heap. É necessário reconciliar esses objetos e os assets vivos com o runtime atual. A consulta implementada não substitui esse ciclo e não prova que os registries de classes/pools estejam vazios. HSD_StartRender e o estado de render também permanecem pendentes. Mario/Link ainda não são criados pelo caminho original.

TrainingPreview: os probes HSD passaram, mas a navegacao automatica parou no menu de 1 jogador e expirou em 180 segundos. Nao foi validado o ciclo completo de Training nesta revisao. A XEX de teste fica em work/xenia-test/package/default.xex; o pacote RGH anterior foi preservado.

Teste basico Xenia aprovado: probes HSD/allocator, intro e 120 Present calls. Evidencia: logs/hsd-arena-ownership-runtime.txt. O sucesso do boot nao resolve o timeout de Training; pacote RGH anterior mantido.

Atualizacao posterior: TrainingPreview passou em reexecucao sem alteracoes na navegacao. O novo probe de ciclo de pools tambem passou; pacote atualizado. Veja hsd-pool-lifecycle-progress.md.
