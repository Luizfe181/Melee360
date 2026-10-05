# GX: cópia do EFB para texturas — 2026-10-03

As auditorias Mario/Link, com e sem boot HSD, caíram de **44 para 41 símbolos pendentes**, sem duplicações. Foram implementados `GXSetTexCopySrc`, `GXSetTexCopyDst` e `GXCopyTex`, com um caminho nativo de cópia funcional. **Essas APIs ainda têm modos sem suporte; presença no link não significa implementação completa de todos os formatos GX.** Fighter continua sem link e sem execução.

## Caminho implementado

O backend faz resolve do render target Xenon, aguarda a GPU, desfaz o tiling nativo, aplica o filtro vertical e escreve os blocos originais de textura no destino RAM. Resolve também render targets RGB565 com quatro amostras. A quantização 5/6/5 é aplicada antes do filtro: o primeiro teste mostrou que o Xenia podia conservar precisão maior na leitura do resolve. Requantizar os canais é idempotente para valores já quantizados pelo hardware.

Formatos de destino suportados: RGB565, RGB5A3 e RGBA8. As palavras são big-endian; RGBA8 tem planos AR e GB separados em blocos 4×4 de 64 bytes. Dimensões não múltiplas de quatro usam blocos completos, com padding inicializado e sem escrever depois do tamanho calculado. O destino precisa estar alinhado a 32 bytes. Os formatos de EFB atualmente suportados não armazenam alpha, portanto a cópia recebe alpha 255.

Os parâmetros de filtro, clamp e clear são compartilhados com o copy engine XFB existente. O filtro mantém os coeficientes agrupados das linhas superior/central/inferior, divisão inteira por 64, wrap de nove bits e saturação. Gamma de cópia de display não é aplicado à cópia de textura. A precisão da filtragem/AA nativa continua sujeita às limitações já documentadas do Xenos frente ao GameCube.

Com `clear=true`, a cópia captura o conteúdo anterior e depois limpa somente o retângulo de origem, respeitando habilitação de escrita de cor/profundidade e os valores de GXSetCopyClear. Os testes desta revisão comprovam a limpeza de cor, preservação dos pixels externos e conteúdo pré-clear no destino. A limpeza de profundidade usa a rotina de profundidade existente, mas não recebeu um teste GPU adicional específico de GXCopyTex nesta revisão.

## Validação

- Host: 459 pixels decodificados contra resultados independentes, incluindo alpha RGB5A3, planos RGBA8, bordas parciais, capacidade insuficiente, formatos/dimensões inválidos e sentinela depois do destino.
- Xenia: **32 cópias GPU e 1.352 pixels**, em render targets RGB8 e RGB565/4×. Três tamanhos, três formatos, retângulos com origem deslocada, tiles parciais, filtro vertical, quatro combinações de clamp e cópia/clear/preservação externa.
- Regressão: percurso de Training e preview Battlefield com perfil AA. Os probes AX, TEV, fog, raster e VI/XFB continuam exigidos pelo verificador.

O teste GPU usa a cópia real e decodifica os bytes com o decoder GX já existente. Não afirma que o gameplay original passou a usar automaticamente essas APIs, nem que houve nesta revisão um teste adicional de amostragem GPU da textura copiada. Probes pesados continuam restritos a verification.flag.

## Limites explícitos

O backend rejeita redução pela metade (`mipmap=true` em GXSetTexCopyDst), cópia de profundidade, intensidade/IA, formatos CTF e dimensões de destino diferentes da região de origem. Não retorna sucesso silencioso nesses casos. RGBA6 do EFB e sua política de alpha não estão implementados.

O caminho inicial usa readback sincronizado e conversão CPU; seu custo aumenta com a área copiada. Isso prioriza correção funcional e não representa a otimização final de efeitos em tempo real. O renderer de menus/previews mantém seu caminho existente.

Restam **41 nomes**: 12 GX, 12 MCC, 6 THP, 4 AI, 3 OS, 2 AX e 2 de stack. A inicialização/mixer DSP e a execução do Fighter seguem bloqueadas.

## Arquivos e evidências

- `src/gx_copy_codec.cpp`, `src/gx_copy_codec.h`: encoder de blocos.
- `src/gx_copy_texture.inc`: backend e probe GPU, incluído por gx_direct.cpp.
- `src/xfb_xbox.cpp`: acesso aos parâmetros compartilhados do copy engine.
- `tests/gx_copy_codec_host.cpp` e `verify-gx-copy.ps1`: testes host.
- `logs/gx-copy-host.txt`, `logs/gx-copy-build.txt`, `logs/gx-copy-training-passed.log`, `logs/gx-copy-aa-stage-passed.log`.
- `logs/gx-copy-fighter-audit.txt`, `logs/gx-copy-hsd-audit.txt` e inventário GX atualizado.

As três rotinas de hardware foram traduzidas para o backend nativo; não são os corpos FIFO originais chamados diretamente. Os setters originais em GXFrameBuf.c e os layouts de textura em GXTexture.c serviram de referência local. A base work/melee-base foi preservada.

## Build publicada

SHA-256: B691407ACC57946259A446889D2ECF626526EE9F3B54C8F14D4637773A5F015F

package/RGH/Melee360/default.xex atualizado; backup work/default-before-gx-texture-copy.xex. Validação nesta revisão apenas no Xenia. O pacote de produção não recebeu verification.flag ou hsd-aa.flag.
