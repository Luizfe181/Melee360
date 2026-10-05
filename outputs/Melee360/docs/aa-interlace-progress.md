# AA e entrelaçamento — atualização 2026-10-03

## Resultado

A cópia filtrada XFB passou nos testes de bytes e está disponível no runtime: sete coeficientes agrupados em três linhas, truncamento por 64, wrap de nove bits, gamma 1.0/1.7/2.2, clamp e composição dos dois campos. O caminho padrão permanece progressivo, com filtro desabilitado e gamma 1.0. O histórico registra a imagem anterior para uma troca posterior de campo.

Também existe teste de rasterização **RGB565 com MSAA 4x real do Xenos**. Ele passou com 62 pixels de cobertura parcial na borda de um triângulo de 64×64. **Isso é um teste do alvo nativo, não AA completo integrado ao HSD ou à gameplay.** A configuração AA do HSD continua rejeitada até RGB565/Z16 e dimensões originais estarem integrados.

Build final publicada em `package/RGH/Melee360/default.xex`, SHA256 `AD31E2BA6C2A26AFF8C022C99F6EF3C5A27BD0D63211FAD7E98C7A4671BE71A2`. Backup anterior: `work/default-before-aa-readback.xex`. Pacote sem flags de diagnóstico.

## Correções encontradas

1. A falha anterior de cores claras estava no critério de comparação: vermelho 200 solicitado ao Clear já resultava em byte 228 na cópia direta de referência, devido ao caminho de formato/gamma nativo. Snapshot, cópia direta e cópia filtrada tinham o mesmo byte 228. Comparar o resultado decodificado pelo sampler sRGB com o argumento do Clear não validava os bytes da cópia. O teste passou a usar LockRect/untile após a GPU terminar, comparando bytes de origem e destino. Os primeiros resultados de falha ficam preservados como histórico, e não representam o resultado atual.
2. A cópia em faixas de 16 linhas falhou ao atingir certas posições no destino tiled. Faixas de 32 linhas corrigiram os casos testados, incluindo a fronteira 239/240 e a linha 479 da escala 242→480. Não concluir apenas por telas de cor uniforme, que ocultavam essa falha.
3. O histórico usa textura independente da apresentação. Reutilizar o front buffer como entrada aplicava a decodificação sRGB e alterava as linhas preservadas.
4. O quad de cópia corrige o alinhamento de meio pixel e seleciona coordenadas inteiras de origem antes do fetch.

## Implementação

- `src/xfb_filter.hlsl`: shaders de cópia, filtro/gamma, campo anterior e teste branco MSAA.
- `compile-xfb-shaders.ps1`: FXC VS/PS/PSCheck/PSWhite; headers locais gerados.
- `src/xfb_xbox.cpp`: snapshot, histórico por XFB, superfície temporária de 32 linhas em EDRAM, cópias Resolve, restauração de targets/estado/viewport, leitura de pixels e testes de MSAA.
- `GXSetDispCopyYScale`: mesma quantização original `iScale=(u32)(256/value)&0x1ff`, escala efetiva `256/iScale` e altura truncada. Aceita escalas finitas ≥1 que tenham divisor não nulo.
- `GXSetDispCopySrc/Dst` e `GXCopyDisp`: sub-regiões e destinos dentro das texturas registradas. O caminho rápido só é usado para cópia completa com escala 1, sem filtro/gamma/campo.
- `GXSetFieldMode`: seleção de paridade aplicada durante a cópia XFB. HalfAspect ainda rejeitado.
- `Melee360HsdRenderConfigure`: preenche posições 6,6 e filtro progressivo `{0,0,21,22,21,0,0}` na configuração nativa; funções originais HSD preservadas.

`game:\xfb-filter-probe.flag` executa testes demorados no boot. Não é necessária para habilitar as APIs implementadas e não está no pacote normal. A flag não habilita AA completo no menu.

## Validação

- Release/Compat compilou pelo XDK, sem /FORCE e sem stubs novos.
- 48 casos de identidade/gamma (16 intensidades em cada gamma), abrangendo valores baixos, altos e fronteiras de 127/128 e 191/192; comparação exata dos bytes.
- Identidade comparada também com Resolve direto, sem shader, para gamma 1.0.
- Coeficientes verticais e wrap de nove bits: 441×255/64 → 1757 → 221, confirmado na GPU.
- Escala quantizada 242→480: seis linhas de saída comparadas com as linhas calculadas da origem.
- `clear=false`: EFB preservado após cópia.
- Ambos os campos em onze linhas, incluindo 31/32, 63/64, 239/240, 479/480 e 719.
- RGB565/MSAA 4x: pixels internos brancos, externos pretos e 62 pixels de borda parcialmente cobertos.
- Evidência: `logs/aa-color-runtime-passed.log`, `logs/aa-color-xenia.txt`, `logs/aa-color-build.txt` e `logs/aa-color-shaders.txt`.
- Regressões da build final: `logs/aa-final-training-xenia.txt` e `logs/aa-final-stage-xenia.txt`.

## Atualização em 2026-10-03

EFB AA, profundidade Z16 e tamanhos EFB/XFB separados foram integrados ao perfil progressivo SCREEN. Consulte [hsd-aa-integration-progress.md](hsd-aa-integration-progress.md) para testes e limites. A lista abaixo registra os bloqueios anteriores; itens 1, 2 e 4 foram atendidos nesse perfil.

## Bloqueios registrados antes da integração

1. Integrar EFB RGB565 multiamostra à seleção de formato do HSD. O teste nativo isolado não libera `GX_PF_RGB565_Z16`.
2. Profundidade Z16 linear/comprimida: Xenon usa depth nativo D24S8; implementar e validar a quantização/compressão original, em vez de aceitar o enum sem equivalência.
3. Padrão GX de três amostras por pixel com posições que variam em 2×2: MSAA 4x do Xenos tem padrão diferente. O teste 4x não prova equivalência desse padrão.
4. EFB/XFB com tamanhos físicos separados, por exemplo 640×242 → 640×480. A escala foi testada em uma sub-região do alvo atual; ainda não é troca completa de modo original.
5. Cópias TOPHALF/BOTTOMHALF do HSD fazem offsets em endereços XFB e escrevem também em um buffer temporário. Os handles de textura atuais são opacos e não implementam esses endereços parciais. Não substituir esses destinos por cópias ignoradas.
6. Campos em meia altura, halfAspect/line/point footprints e scanout físico 480i no console. Os testes deste turno foram no Xenia, em janela progressiva.

Auditorias final e HSD: 69 símbolos ausentes, zero duplicações, Fighter ainda não linkado/executado. Evidência: `logs/aa-final-audit.txt` e `logs/aa-final-hsd-audit.txt`.

A base decomp original permanece separada e `git status --porcelain` retornou vazio. A contagem de símbolos não mede esta conclusão; o teste Fighter ainda exige outras dependências.

## Fontes

Contratos e presets: código local original HSD `video.c`, GX `GXFrameBuf.c` e headers XDK. Aritmética de filtro comparada com o [Dolphin TextureConversionShader](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/TextureConversionShader.cpp), sem copiar corpos GPL para o port. O [artigo técnico do Xenia](https://xenia.jp/updates/2021/04/27/leaving-no-pixel-behind-new-render-target-cache-3x3-resolution-scaling.html) explica diferenças de gamma do Xenos e sRGB; os resultados acima são dos testes locais.
