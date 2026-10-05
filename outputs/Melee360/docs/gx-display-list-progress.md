# Executor de display lists GX — 2026-10-02

GXCallDisplayList agora interpreta listas de primitivas no backend Xbox:
TRIANGLES, QUADS, TRIANGLESTRIP e TRIANGLEFAN, formato VAT 0–7 e NOP/padding.
Faz uma passagem estrutural sobre a lista inteira antes de enviar desenhos:
opcode, formato, contagem, tamanho dos registros e limites do buffer.

Posições diretas XY U8 ou XY/XYZ F32; CLR0 direto ou indexado 8/16;
TEX0 direto ou indexado 8/16. A leitura de índices/counts é big endian;
F32 usa memcpy no alvo big endian nativo. Os atributos são enviados pela
mesma rotina de vértices/GPU já testada. Não acessa o FIFO do GameCube.

Testes Xenia: lista direta com RGBA8 e UV U8, padding até 32 bytes; lista
com RGB565 indexado em 256–258 e UV indexada. Verifica cores/UVs, conclusão
dos vértices e submissão à GPU. Logs: gx-display-list-build.txt,
gx-display-list-xenia-final.txt e gx-display-list-audit.txt.
Auditoria Fighter: 140 símbolos ausentes, zero duplicatas.

Suporte parcial: não interpreta comandos CP/BP/XF, nested display lists,
posições indexadas, normais/NBT, índices de matriz, TEX1–7 ou geração de UV.
Esses casos são rejeitados, não ignorados. A textura direta ainda é branca:
não houve implementação de TEV, iluminação ou integração com a execução
completa de HSD_PObjDisplay. A remoção do símbolo do linker não significa
GXCallDisplayList completo nem que o Mario possa ser renderizado pelo HSD.

Ainda não há Fighter executando nem frame de gameplay. Nenhuma mudança de
áudio neste incremento; nenhuma edição na base original. Console físico
ainda precisa de validação.

Regressão final no Xenia concluída com exit 0; os probes diretos e indexados passaram. Falta validação em console físico.
