# Ampliação GX — 2026-10-03

Esta revisão integra mais caminhos reais GX, sem stubs e sem `/FORCE`. **Não conclui todo o GX.** O caminho auditado de criação Mario/Link caiu de 69 para 64 símbolos ausentes; 15 deles ainda são GX. Ambas as auditorias têm zero duplicações. Fighter continua sem link/execução.

## Primitivas e rasterização

`GXSetLineWidth`, `GXSetPointSize`, `GXEnableTexOffsets`, `GXGetLineWidth` e `GXGetPointSize` agora têm implementação nativa. `GX_POINTS`, `GX_LINES` e `GX_LINESTRIP` usam expansão de geometria no CPU e triângulos no Xenon. Preservam profundidade homogênea, cores e oito UVs. Larguras usam unidades originais de 1/6 pixel, offsets usam ZERO/1⁄16/1⁄8/1⁄4/1⁄2/ONE. Linhas são recortadas nos planos de profundidade antes da divisão por w; pontos atrás da câmera são rejeitados.

O raster usa expansão pelo eixo dominante, não caps circulares. Casos degenerados/diagonais extremos e cobertura subpixel exata do GameCube permanecem sem certificação em hardware. Isso não é uma equivalência bit a bit do rasterizador inteiro.

Display lists primitivas também aceitam esses três tipos. `GX_CULL_ALL` descarta polígonos, preservando linhas e pontos. Não foram acrescentados handlers vazios para comandos de estado em display lists: esses comandos continuam exigindo sua própria integração.

Arquivos: `src/gx_raster.inc`, `src/gx_raster_probe.inc`, `src/gx_direct.cpp`, `src/gx_display_list.inc`, `src/gx_xbox_state.cpp`.

## Fog original e profundidade

Os corpos originais de `GXSetFog` e `GXSetFogRangeAdj` são extraídos de `GXPixel.c`. Os writes dos registradores E8..F2 alimentam um backend de shader; apenas o cache FIFO `bpSent` foi removido dessa tradução. A aritmética e a quantização originais dos registradores foram preservadas. Proveniência e adaptações em `logs/portable-gx-provenance.json`.

O renderer GX direto aplica NONE/LIN/EXP/EXP2/REVEXP/REVEXP2, preserva alpha e usa profundidade modificada por Z-texture quando ativa. Range adjustment usa os valores da tabela original, com interpolação dos coeficientes entre intervalos de 32 pixels. **A interpolação é uma aproximação declarada: a precisão subpixel do hardware não foi comprovada.** O renderer de previews possui caminho próprio; compilar esses setters não significa que todas as cenas já passaram pelo renderer original HSD.

A integração revelou e corrigiu a conversão anterior de profundidade em `gx_transform.c`. O viewport original GX trabalha com clip z entre -w e 0 e offset far; o intervalo nativo correto é `w + z`, não simplesmente `-z`. Testes verificam near→0 e far→w em perspectiva e ortográfica. As projeções artificiais dos testes Z-texture foram atualizadas para manter os mesmos valores de profundidade esperados.

Também foi limitado o arredondamento de profundidade ao máximo 0xFFFFFF: somar 0,5 em float ao extremo de 24 bits podia produzir 0x1000000 e wrap indevido.

Arquivos: `src/gx_fog.inc`, `src/gx_fog.hlsl`, `src/gx_fog_probe.inc`, `src/gx_direct.hlsl`, `src/gx_tev_probe.inc`, `src/gx_transform.c`.

## Validação

- 768 verificações de offsets nas oito unidades e seis enums.
- 26 verificações de cobertura exata na GPU: pontos, linhas horizontais/verticais, strip, largura zero/1/2/8 pixels, perspectiva, recorte de profundidade e cull ALL.
- Três display lists primitivas decodificadas e submetidas à GPU.
- Dez valores conhecidos da tabela original de fog e 100 casos GPU de cor/profundidade/range/alpha. Comparação independente em eye distance, tolerância de dois níveis RGB devido à quantização original.
- As 694 verificações TEV e 144 verificações GPU Z16 continuam passando.
- Testes host: transformação near/far e objetos GX/fog-register passaram.
- Battlefield com AA: quatro variantes × 120 atualizações; zero meshes descartados. Continuam pendentes os callbacks de cenário já registrados (até quatro); continua sendo preview, sem partida.

Evidências: `logs/gx-expanded-aa-stage-passed.log`, `logs/gx-expanded-final-build.txt`, `logs/gx-fog-shaders.txt`, `logs/gx-transform-host-build.txt`, `logs/gx-expanded-cpu-host.txt`, `logs/gx-expanded-fighter-audit.txt`, `logs/gx-expanded-hsd-audit.txt`.

O XDK continua emitindo timeout do verificador estático de microcode do combiner dinâmico; a compilação termina e os testes de execução passam. Não se afirma certificação estática completa. Testes realizados no Xenia, não no console real.

## Inventário e bloqueios para concluir GX

`diagnostics/inventory_gx.py` cruza os headers públicos originais com símbolos definidos nos objetos Release/Compat reais. Resultado: 250 APIs, 102 símbolos compilados, dois wrappers inline originais e 146 sem símbolo runtime. **Os números cobrem o SDK público, não apenas dependências do Fighter; presença de símbolo não mede completude ou percentual de port.** [Inventário completo](gx-api-inventory.md).

Prioridades reais no caminho HSD/Fighter:

1. Iluminação e normais: `GXLoadLightObjImm`, `GXNormal3f32`, `GXSetNumChans`, `GXSetChanCtrl`, `GXSetChanAmbColor`, `GXSetChanMatColor`. Exigem fluxo de normais, canais e atenuação/difusão/especular; não basta registrar o estado.
2. Texgen: `GXSetNumTexGens`, `GXSetTexCoordGen2`. Exigem fontes de posição/normal/UV, projeção STQ, matrizes e normalização/post-matrix.
3. EFB→textura: `GXSetTexCopySrc`, `GXSetTexCopyDst`, `GXCopyTex`. Exigem formatos/tile layout, profundidade, redução mip e propriedade dos buffers usados pelo HSD; Resolve XFB não substitui essa cópia.
4. PE/formatos: `GXSetZCompLoc`, `GXSetDither`, `GXSetDstAlpha`. Exigem early/late depth, RGBA6 e preservação do alpha usado para blend, além de formatos EFB atualmente limitados.
5. `GXInvalidateVtxCache`: integração do cache de arrays/display lists com o backend nativo, sem descartar alterações de memória.

Também permanecem comandos completos de estado em display lists, viewport fracionário/jitter, TOPHALF/BOTTOMHALF com offsets XFB, halfAspect e equivalência do padrão AA GX de três amostras. O perfil Xenon 4x é aproximado.

A base `work/melee-base` continua intacta.

## Referências

Semântica principal: GX original local (`GXGeometry.c`, `GXPixel.c`, `GXTransform.c`, `MTXFrustum/MTXOrtho`) e headers XDK. Foram consultados [GeometryShaderGen](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/GeometryShaderGen.cpp), [ShaderGenCommon](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/ShaderGenCommon.cpp), [UberShaderPixel](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/UberShaderPixel.cpp) e [PixelShaderManager](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/PixelShaderManager.cpp) para verificar contratos e limites; corpos GPL não foram copiados. A tradução nativa desta revisão está nos arquivos do port indicados acima.

## Pacote publicado

XEX final: `package/RGH/Melee360/default.xex`; SHA256 `2448E8518B87585AB9FACED8F54C4DBB0788EB131DCADA9E7596870C2FD38347`.
Backup: `work/default-before-gx-expanded.xex`. Perfil AA continua opcional via `profiles/hsd-aa.flag`, copiado para junto de `default.xex`.

Training sem AA na candidata final também passou: `logs/gx-expanded-final-training-passed.log`. A XEX publicada contém as implementações testadas e o verificador exige os novos marcadores de sucesso de raster, fog e display lists.
