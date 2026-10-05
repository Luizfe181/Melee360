# GX viewport/cull e troca de música

GXSetViewport/GXSetViewportJitter configuram D3DVIEWPORT9; GXGetViewportv conserva os seis valores GX. O backend atual admite coordenadas físicas inteiras e profundidade entre zero e um. Jitter segue o ajuste original de meio pixel, mas rejeita origem fracionária: o ajuste completo exige offset no shader e ainda falta. Não há escala automática de coordenadas 640x480 para 1280x720. Os viewers usam explicitamente 1280x720.

GXSetCullMode configura NONE/FRONT/BACK no D3D; GX_CULL_ALL é rejeitado, pois precisa suprimir submissão de geometria. A orientação FRONT/BACK ainda precisa de comparação visual com geometria de referência; os viewers existentes preservam NONE. Assim, não há alegação de cobertura completa dessas APIs.

O diagnóstico Battlefield agora seleciona audio/vl_battle.hps; ao retornar ao seletor, seleciona menu01.hps. A faixa foi escolhida explicitamente para o diagnóstico; não é execução da tabela original de despacho de músicas. O mesmo decoder/streaming XAudio2 é usado e o volume Música vale para ambas. Troca de faixa libera a voz/buffers antes de substituir o archive. Continua leitura síncrona da faixa na transição, que pode causar uma pausa e precisa ser medida no console. Intro/título e SFX permanecem pendentes.

A fronteira de chamadas passa a distinguir silêncio, menu e palco. Não há GXBegin/FIFO/TEV completo, matriz original consumida pelo pipeline nem mixer AX/DSP completo nesta etapa. A correção de cache do seletor foi mantida.

Verificação: build retail empacotada; auditoria 201 símbolos/528 referências/zero duplicatas. Xenia percorreu as quatro variantes animadas de Battlefield, retornou ao seletor e confirmou streaming/consumo de PCM de vl_battle e retomada de menu01. A base original permanece sem alterações. Desempenho e áudio desta revisão ainda precisam de validação no console físico.
