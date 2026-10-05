# Posições inteiras GX — 2026-10-02

GXCallDisplayList passa a decodificar posições XY/XYZ U8, S8, U16, S16 e F32, diretas ou indexadas. Inteiros de 16 bits são lidos em big-endian; formatos com sinal preservam coordenadas negativas e a escala usa 2^-frac. O caminho compartilha transformação e submissão com as posições F32 existentes.

Validação: compilação Release/Compat com XDK; testes nativos de S16 XYZ direto e INDEX16 nos índices 256–258 com stride 8, negativos e frac=2; S8 XY negativo e U16 XY frac=9. Coordenadas transformadas verificadas e triângulos enviados ao GPU. Regressões intro/áudio e Training/CSS/seleção de cenário passaram no Xenia. Logs: gx-integer-build.txt, gx-integer-intro.txt e gx-integer-training.txt. O verificador agora exige o marcador do novo teste. A base work/melee-base permaneceu limpa.

Escopo: ampliado o leitor de posições das display lists; não foram adicionados todos os emissores imediatos de inteiros. Normais, índices de matriz, comandos CP/BP/XF, TEV e texturas no backend direto continuam incompletos. O backend direto ainda usa textura branca. Não houve nova implementação AX/DSP nesta etapa; opening.hps e transição para áudio do menu passaram na regressão. Não comprova funcionamento no console físico ou execução de Fighter_Create/gameplay.
