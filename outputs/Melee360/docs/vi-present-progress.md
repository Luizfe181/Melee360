# VI por apresentações reais

VIInit, VIGetRetraceCount, VISetPreRetraceCallback e VISetPostRetraceCallback foram adicionados como adaptador de limites de apresentação. Init é idempotente e preserva callbacks. Setters devolvem callbacks anteriores. O runtime chama pre antes de Present; em sucesso incrementa o contador e chama post. Em falha, pre já ocorreu mas o contador e post não avançam. Callbacks rodam na thread de render, não em interrupção física.

O probe verifica ordem/números e falha sem incremento; restaura o contador e callbacks após o teste para não persistir quadros sintéticos. O frame inicial de diagnóstico não entra no contador. A contagem representa apresentações posteriores do port, não todos os vblanks físicos que possam ocorrer durante quedas de FPS. Não é VI completo.

Não foram adicionadas implementações vazias para VIConfigure, VIFlush, VISetNextFrameBuffer, VISetBlack, VIWaitForRetrace ou status de vídeo. XFB ainda exige conversão/apresentação real dos buffers. O scheduler completo HSD continua desconectado. GX/TEV, AX/DSP e OS completos seguem pendentes; esta revisão implementa apenas essa parte VI.
