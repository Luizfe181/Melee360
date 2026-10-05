# GX transformações — banco CPU

Seis símbolos: GXLoadPosMtxImm, GXLoadNrmMtxImm, GXLoadTexMtxImm, GXSetCurrentMtx, GXSetProjection e GXGetProjectionv. Bancos de dez matrizes de posição/normais (IDs 0..27, múltiplos de 3) e dez de textura (30..57). Matriz de normais lê o bloco 3x3 de uma 3x4; matrizes de textura aceitam 2x4/3x4. Valores não finitos e IDs inválidos são rejeitados. Post-texture matrices não estão cobertas.

Os consumidores Melee360GXTransformPosition/Normal/Texcoord realizam operações CPU sobre os bancos. A posição usa os seis coeficientes de projeção GX, w=-z para perspectiva, w=1 para ortográfica e converte z clip negativo GX para positivo Xbox. O banco não substitui o renderer direto atual, e ainda precisa ser ligado ao caminho GXBegin/atributos/vértices. Não afirmar desenho por GXLoadPosMtxImm nesta etapa. Input/output dos consumidores devem ser buffers distintos.

O teste host passou transformação de posição, extração/transformação de normais, textura 2x4, packing de projeção, seleção do último slot e convenção de profundidade. Renderer original parcial e correção de cache do seletor preservados. Nenhum shader TEV completo ou mixer AX foi implementado nesta revisão.

Build retail empacotada. Auditoria: 187 pendências/456 referências/zero duplicatas. Teste Xenia CSS passou até o retorno ao título; isso verifica ausência de regressão nas cenas atuais, não execução do banco de matrizes no desenho. A verificação numérica do banco foi feita no host.
