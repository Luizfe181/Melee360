# Pesquisa Dolphin: cópias EFB e texturas — 2026-10-04

Referência fixada no commit eb236466c4f0ec8bef619add0972353d3996fe6c do repositório oficial. Snapshot de leitura em work/dolphin-reference; hashes em logs/dolphin-reference-manifest.json. Nenhum código do Dolphin foi integrado ao projeto e nenhuma XEX foi alterada nesta pesquisa.

## Achados no Dolphin

CopyRenderTargetToTexture cria entradas de cópia no cache GPU. CopyEFBToCacheEntry usa um pipeline de conversão para produzir a textura; o carregamento pode reutilizar entradas quando a memória continua válida. Há tratamento de regiões sobrepostas e alterações de conteúdo. O caminho RAM pode usar staging adiado, consolidado por FlushEFBCopies. Esses caminhos dependem de configuração e capacidade do backend; não significam que toda cópia evita RAM. [Código oficial: TextureCacheBase.cpp](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/VideoCommon/TextureCacheBase.cpp#L2148).

O gerador de conversão GPU aplica filtro e quantização de formato. Para R4, replica o vermelho quantizado também no alfa; não basta copiar RGBA do framebuffer. [TextureConverterShaderGen.cpp](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/VideoCommon/TextureConverterShaderGen.cpp#L140).

VertexManagerBase registra acessos CPU e organiza envio de comandos para reduzir esperas de readback; sem acessos CPU, mantém mais trabalho agrupado. [VertexManagerBase.cpp](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/VideoCommon/VertexManagerBase.cpp#L965).

## Comparação com o port

| Caminho | Implementação observada |
|---|---|
| Port atual | Resolve → espera → untile/filtro CPU → encode GX em RAM → decode/cache/upload ao carregar textura |
| Dolphin com cópia VRAM | Conversão GPU → entrada de textura GPU reutilizável, com caminho RAM separado |

Em Melee, HSD_ShadowInit pede cópia 0x20; HSD_ShadowEndRender usa GXCopyTex, GXPixModeSync e GXInvalidateTexAll. Nosso decoder I4 expande o nibble vermelho em R/G/B/A. O formato e esses pontos de sincronização definem um alvo inicial concreto: sombras de Battlefield 256×256. A melhoria anterior de recorte não removeu o percurso completo.

## Adaptação proposta — inferência para nosso projeto

1. Implementar inicialmente cópia GPU nativa para R4/I4 das sombras, preservando filtro, clamp, quantização, alfa e clear. Na carga da imagem correspondente, reutilizar a textura GPU.
2. Manter encode e atualização RAM imediatos nesta primeira etapa. Conferir bytes RAM, endereço, tamanho e formato antes de reutilizar; se houver mutação ou uso incompatível, executar o decoder/upload existente. Invalidar sobreposições e conservar recursos até os desenhos anteriores terminarem.
3. Só depois estudar adiamento do readback. O port usa ponteiros C nativos; leituras RAM não passam necessariamente por um ponto interceptável de memória emulada. Precisamos auditar consumidores e introduzir materialização explícita onde necessário. Não presumir que o esquema de staging do emulador é diretamente equivalente.

A primeira etapa busca remover decode/reupload redundante, sem dispensar RAM correta. Ainda não foi implementada; o ganho depende do comportamento real de cache e da comparação no Xenia/console. Mesmo uma melhora neste caminho não elimina o custo alto de montagem de vértices medido anteriormente.

Validação exigida: comparação dos pixels GPU e bytes RAM com o caminho atual, mutações de imagem, regiões sobrepostas, filtros e bordas, RGB/alpha, clear, vida dos recursos, 900 frames originais, Training e menus. Medição pareada com o caminho antigo no mesmo binário. A pesquisa orienta a mudança arquitetural; não é evidência de FPS futuro.
