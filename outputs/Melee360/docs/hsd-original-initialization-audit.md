# Inicializacao original HSD: compilacao e dependencias

Foi criado diagnostics/generate_hsd_main_heap.py. Ele extrai os corpos originais de HSD_CreateMainHeap, HSD_ObjInit (helper privado), HSD_GetCurrentRenderPass e HSD_StartRender, sem alterar suas instrucoes. Somente os caminhos relativos dos includes foram qualificados. O hash do fonte e a proveniencia ficam em logs/hsd-main-heap-provenance.json. A base decomp permaneceu intacta.

A opcao -HsdMainHeap da auditoria MarioLink inclui essas rotinas e conserva os callbacks originais de classes/pools. Os objetos e entry ficam em build/fighter-create-audit-hsd-main-heap, separado da auditoria normal. O entry e somente de link, nao possui inicializacao para execucao: current_heap comeca em -1 e o modo VI tambem precisaria de HSD_InitComponent. Nao executar este entry.

## Resultado verificado

Comando: ./audit-fighter-create.ps1 -MarioLink -HsdMainHeap.
Os quatro corpos compilaram com XDK. Auditoria ampliada: 111 ausencias, zero duplicacoes, linked=false, executed=false, packaged=false. Log: logs/hsd-main-heap-audit.txt.

A comparacao exata das listas foi verificada: HSD_CreateMainHeap, HSD_GetCurrentRenderPass e HSD_StartRender deixam de estar ausentes; GXSetFieldMode e GXSetPixelFmt passam a ser dependencias. Delta em logs/hsd-main-heap-dependency-delta.json.

A auditoria normal foi repetida e permanece com 112 ausencias, zero duplicacoes: logs/hsd-baseline-regression-audit.txt. Nao houve mudanca na XEX executavel nesta etapa; ela conserva a build anterior validada em Training. Nao foi necessario repetir testes Xenia para uma alteracao exclusivamente de auditoria.

## Bloqueios concretos

1. HSD_CreateMainHeap continua sem poder rodar sobre os menus ativos. A rotina original invalida classes/pools e destroi o heap em bloco; paginas de pools permanecem alocadas mesmo com used=0. O shutdown de seus consumidores precisa preceder o descarte.
2. HSD_StartRender consulta HSD_VIGetRenderMode, define o passe e aplica pixel format/field mode. GXSetPixelFmt e GXSetFieldMode precisam traduzir formato de cor/depth, field rendering e comportamento de framebuffer. Ignorar as chamadas ocultaria esta dependencia.
3. A auditoria ainda nao liga, por GX/AX/VI/OS e demais dependencias da lista. Nem Mario nem Link foram criados. Compilar o helper HSD_ObjInit nao comprova pools inicializados em runtime.

O proximo passo e estabelecer o modo VI e o contrato de framebuffer usado por HSD_StartRender, e implementar seus consumidores GX com validacao do render target, antes de promover esse trecho ao runtime.
