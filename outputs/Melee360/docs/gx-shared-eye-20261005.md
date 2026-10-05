# Compartilhamento da posição de câmera para projeção e iluminação — 2026-10-05

## Comportamento anterior e decisão

emitPosition em gx_direct.cpp transformava o mesmo ponto duas vezes com a mesma matriz: GXTransformPositionSlot calculava eye[3] para a projeção, e GXTransformEyePosition repetia a multiplicação para eyePosition usado pela iluminação. As matrizes não mudam entre essas duas chamadas.

**ADAPTAR** essa fronteira da tradução, sem alterar gameplay/HSD, número de vértices/luzes ou algoritmos de iluminação/texgen. O ganho potencial vem de eliminar uma multiplicação de posição, não de aproximar funções. **MANTER** os consumidores antigos como referência e **MANTER A TRADUÇÃO** dos demais modos GX.

## Alteração mínima

Melee360GXTransformPositionAndEye fornece ambas as saídas. Mantém a mesma sequência de somas/produtos, projeção e conversão de profundidade. Checa slot, validade da matriz e ponteiros. Não guarda resultados entre vértices ou frames e não adia atualização de matrizes.

Flag opcional game:\gx-shared-eye.flag. Sem ela, continuam as duas chamadas anteriores. O benchmark desta rodada não liga gx-native-submit.flag nem a experiência de reuso RGB, isolando a alteração.

A revisão de texgen identificou cópias dos oito conjuntos de UV a cada vértice. Um plano futuro pode guardar somente fontes necessárias, mas precisa respeitar as coordenadas de entrada originais versus coordenadas geradas e a restauração de estado dos probes. Nenhuma alteração de texgen foi aplicada nesta rodada. O reuso RGB de iluminação já tinha sido testado anteriormente; não foi refeito nem declarado novidade.

## Validações concluídas

- Release/Compat XDK compilou com sucesso.
- Host VS2010: 1.280 comparações byte a byte entre as funções antigas e a combinada, dez slots de matriz, projeções perspectiva/ortográfica, pontos positivos/negativos e parâmetros inválidos. Todas passaram; testes existentes de transformação continuaram passando.
- Três partidas originais Mario/Link Battlefield de 180 frames: referência → compartilhada → referência, Xenia silencioso, mesma candidata, sem compilação simultânea.
- Samples de CPU iguais; 203241 draws, 1367 uploads e 345 cópias em todas.

| Métrica | Referência antes | Compartilhada | Referência depois |
| --- | ---: | ---: | ---: |
| Render ms/frame | 315,346 | 308,258 | 313,090 |

Redução observada **1,543–2,248%**; drift das referências **0,715%**. Uma execução por condição, sem intervalo estatístico. São tempos CPU de parede, incluindo esperas; não GPU timestamps ou FPS do console. Indício de benefício modesto, ainda requer repetição/duração/hardware antes de promoção ao padrão.

## Arquivos

- src/gx_transform.c: consumidor combinado; antigos preservados.
- src/gx_direct.cpp: seleção opcional na emissão de posição.
- tests/transform_host.c: comparação exata contra ambos os consumidores de referência.
- diagnostics/run_gx_shared_eye.ps1 e analyze_gx_shared_eye.py: benchmark.
- diagnostics/run_gx_shared_eye_regression.ps1 e analyze_gx_shared_eye_regression.py: Training/probes/capturas.
- logs/gx-shared-eye e logs/gx-shared-eye-{build,host}.txt: evidências.

Pacote publicado não substituído. Próxima prioridade: reduzir trabalho redundante de preparação de texgen com estado atualizado e outputs iguais. Não migrar toda iluminação para GPU sem reproduzir arredondamento/clamp/atenuação e validar modos.
## Resultado final da regressão visual

Training/probes concluídos; duas partidas de 180 frames com captura passaram. Frames 1 e 60 (640×480): **zero pixels alterados**. Samples CPU das execuções com captura iguais. Sem regressão encontrada nos casos testados. Isso não comprova todos os frames/combinações GX nem equivalência integral com GameCube. Nenhum teste físico ou combate de 900 frames nesta rodada.

Scratch restaurado e flags temporárias removidas. Pacote SHA256 95074C0C2CFC7226F2ABE2E88CBB4975411A1A6FD35054DA0FAE079CCE210738 preservado. Manter a mudança opt-in até validação ampliada.