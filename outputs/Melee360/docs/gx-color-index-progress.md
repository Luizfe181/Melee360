# Cores indexadas GX — 2026-10-02

GXColor1x8/GXColor1x16 buscam dados no array CLR0 registrado por GXSetArray.
Suportados RGB8, RGBA8 e RGB565 (big endian), stride explícito, índices 8/16
bits e espera pelos demais atributos antes de enviar o vértice. GXSetArray
é parcial: apenas CLR0; outros arrays ainda são rejeitados, sem no-ops.
O tamanho do array não faz parte da API GX; validade e duração da região
continuam sendo responsabilidade do chamador, como no contrato original.

Probes GPU: RGB8 com padding/stride 6, RGB565 com stride 4 e índices 256–258
(detecta truncamento para 8 bits), RGBA8 com alpha 0/128/255. Ponteiros de
arrays locais são removidos ao terminar o probe. Build XDK e testes Xenia:
logs/gx-color-index-build.txt, logs/gx-color-index-xenia-final.txt.

Auditoria: 143 símbolos ausentes e zero duplicatas. Três nomes saíram da lista,
mas isso não representa a implementação completa de GXSetArray. Posição,
normal, UV indexadas e display lists continuam pendentes. Não há Fighter
original executando; áudio não foi ampliado neste incremento. Base preservada.

A regressão final Training/CSS/Battlefield passou com exit 0, incluindo os índices 256–258 e alpha RGBA8. Validação no Xbox 360 físico ainda pendente.
