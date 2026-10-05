# Overlay FPS e cópias GX — 2026-10-02

Overlay sempre visível no canto superior esquerdo, durante intro, título,
menus e previews. Mostra FPS e tempo médio em ms por frame apresentado,
calculados com QueryPerformanceCounter e atualizados a cada janela de pelo
menos um segundo. Só conta Present com sucesso. FPS: -- indica que a primeira
janela ainda não terminou. É apresentação da XEX, não taxa de simulação de
gameplay, que ainda não executa. Carregamentos/travas entram na média seguinte.

Fonte existente do port; shaders existentes; recursos persistentes próprios,
sem recarregamento de arquivo por frame. Dois desenhos por frame (fundo e texto)
e buffers de vértices de tamanho fixo. Salva/restaura shaders, textura, declaração,
viewport, constante do shader e estados de blend/profundidade/scissor/cor.
Recursos são liberados ao fechar. Há overhead do próprio overlay; desempenho
real precisa ser medido no console.

Otimização GX direto: TRIANGLES passam à GPU pelo vetor original, eliminando
uma cópia inteira de vértices. Quads/strips/fans reservam o espaço calculado
antes da conversão, reutilizando a capacidade nas chamadas seguintes. No probe,
1440 bytes de cópia foram evitados. Isso é evidência de trabalho removido,
não uma medição de ganho de FPS dos menus ou da intro.

Logs: gx-direct-copy-xenia.txt (regressão da otimização), fps-overlay-build.txt
e fps-overlay-xenia.txt (build e regressão do overlay). Implementações GX/AX
pendentes não foram concluídas por esta mudança; base original preservada.

Training/CSS/seleção Battlefield e intro passaram no Xenia (exit 0). Logs confirmam desenho do overlay e cálculo da primeira janela de FPS, além de vídeo avançando e probes anteriores. Falta validação visual e de desempenho em console físico.
