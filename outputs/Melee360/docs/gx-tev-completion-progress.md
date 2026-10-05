# TEV direto e indireto no Xbox 360 — 3 de outubro de 2026

O backend de primitivas GX agora oferece as APIs públicas de `GXTev.h` e `GXBump.h`, com combiner de 16 estágios, texturas indiretas e Z-texture. Isso conclui a implementação desse conjunto de APIs para as entradas e targets atualmente aceitos pelo backend. Não conclui todo o renderer GX/HSD nem torna a partida jogável.

## Implementação

- Seletores de cor e alpha, quatro registradores PREV/REG0/REG1/REG2, cores S10, destinos RGB/alpha independentes e saída do último estágio.
- ADD/SUB, bias, quatro escalas, clamp, comparações R8/GR16/BGR24/RGB8/A8, constantes K, frações e seletores reservados; quatro tabelas de troca RGBA.
- Roteamento entre oito unidades de textura, oito coordenadas UV e duas cores de vértice. O caminho direto, índices INDEX8/INDEX16 e display lists de primitivas transportam essas entradas.
- Quatro estágios indiretos, formatos 8/5/4/3 bits, bias STU, três matrizes e variantes S/T, escalas de coordenadas, wrapping, soma da coordenada anterior, bump alpha e normalização.
- LOD calculado com derivadas originais ou com coordenadas distorcidas, conforme a configuração indireta; usa os mipmaps e paletas já implementados.
- Z8/Z16/Z24X8, DISABLE/ADD/REPLACE, bias e retorno ao início da faixa de 24 bits. A variante de pixel shader com saída de profundidade é selecionada apenas quando Z-texture está ativo.
- `GXSetProjectionv` permite restaurar a projeção sem reconstruir sua matriz.

Os corpos originais de GXSetTevOp, GXSetTevIndWarp, GXSetTevIndTile, GXSetTevIndBumpST, GXSetTevIndBumpXYZ e GXSetTevIndRepeat são preservados. As adaptações se restringem a assertions nativas e casts/enums exigidos por C++. O gerador e o manifesto registram origem, linha e hashes.

**GXSetTevClampMode também preserva seu corpo original:** o próprio Dolphin SDK declara essa API indisponível nesse hardware e termina em assertion. Não foi transformada numa função vazia nem numa implementação fictícia. O clamp operacional continua disponível através de GXSetTevColorOp/GXSetTevAlphaOp.

## Arquivos e reprodução

- `src/gx_tev_state.inc`: estado GX e setters traduzidos para constantes dos shaders.
- `src/gx_tev.hlsl` e `src/gx_direct.hlsl`: combiner, coordenadas indiretas e saída de profundidade.
- `src/gx_vertex_inputs.inc`, `src/gx_direct.cpp`, `src/gx_display_list.inc`: envio de duas cores e oito UVs.
- `src/gx_tev_probe.inc`: testes na GPU, inclusive rejeições esperadas.
- `diagnostics/generate_original_tev_helpers.py`: extração reproduzível dos sete corpos originais, incluindo a API indisponível.
- `logs/original-tev-provenance.json`: hashes e adaptações dos corpos originais.
- `logs/gx-tev-api-coverage.json` e `logs/gx-tev-native-object-symbols.txt`: cobertura de todas as declarações dos dois headers no objeto compilado nativo.

```powershell
$env:XEDK='C:\Program Files (x86)\Microsoft Xbox 360 SDK'
python outputs/Melee360/diagnostics/generate_original_tev_helpers.py --base work/melee-base --project outputs/Melee360
& outputs/Melee360/compile-intro-shaders.ps1
& C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe outputs/Melee360/Melee360.vcxproj /t:Build /p:Configuration=Release '/p:Platform=Xbox 360' /p:DecompMode=Compat
```

A imagem para RGH/Xenia está em `package/RGH/Melee360/default.xex`; seu SHA256 está em `logs/RGH-image-sha256.json`. A base em `work/melee-base` permanece limpa e inalterada.

## Verificação concluída

| Verificação | Resultado |
|---|---|
| Shaders XDK e build Release/Compat | Compilaram e geraram XEX |
| Testes TEV na GPU do Xenia | 694 casos passaram |
| Expansão anterior de texturas | 41 casos GPU passaram |
| TrainingPreview | Passou, incluindo preparação original de regras/seleção |
| StagePreview | Quatro variantes, 120 atualizações cada, zero meshes ignorados |
| Auditoria Fighter_Create Mario/Link | 88 símbolos ausentes, zero duplicatas |
| Auditoria com inicialização HSD ampliada | 86 símbolos ausentes, zero duplicatas |
| Console real nesta revisão | Ainda não testado |

A inclusão do corpo original de GXSetTevClampMode resolveu uma referência adicional no link, embora essa API continue indisponível por seu contrato original; essa redução numérica não representa uma função de renderização nova.

Os 694 casos verificam seletores, destinos, aritmética, comparações, K, swaps, encadeamento de 1 a 16 estágios, formatos/matrizes/bump indiretos, todas as escalas e slots indiretos, funções auxiliares originais, LOD, duas cores/oito UVs e Z-texture. A profundidade é conferida por comparações independentes antes/depois do valor esperado, com margem de 32 unidades de Z24 e controles negativos; isso não é uma leitura bit a bit do depth buffer. Os casos de cor/alpha usam descarte por referência e queries de oclusão reais.

Logs: `logs/gx-tev-full-build.txt`, `logs/gx-tev-shaders-build.txt`, `logs/gx-tev-full-xenia.txt`, `logs/gx-tev-full-stage-xenia.txt`, `logs/gx-tev-full-audit.txt` e `logs/gx-tev-full-hsd-audit.txt`.

O verificador agora exige uma confirmação explícita de sucesso do TEV. Apenas a configuração isolada em `work/xenia-test` usa queries estritas e compilação síncrona de shaders; a configuração pessoal do Xenia não é alterada. Os testes extensos só executam com `verification.flag`.

## Correção do bloqueio de Z-texture

Uma verificação temporária dentro de PSDepth produzia resultados incorretos de profundidade em determinadas combinações. Um shader mínimo confirmou suporte à escrita. A condição do loop foi explicitada com limite de 16 estágios, e a verificação temporária foi retirada do shader final. A validação passou a usar exclusivamente comparações independentes de profundidade, incluindo rejeições esperadas. Todos os casos Z8/Z16/Z24X8 × ADD/REPLACE × dois biases passaram na versão limpa. Esses experimentos não comprovam uma causa interna específica no compilador ou no emulador.

O compilador XDK ainda informa timeout do verificador de microcode no combiner dinâmico; a compilação termina com sucesso, e os testes de execução passaram. Não se afirma que o verificador estático certificou todo o shader.

## Limites que permanecem reais

- O contrato atual usa UVs normalizados e cores já disponíveis no backend direto. Texgen/projeção STQ, iluminação GX, carregamento completo de comandos de estado em display lists, EFB copy e outros modos de framebuffer são trabalhos de outras partes de GX/HSD.
- As escalas de coordenadas atualmente derivam das dimensões das texturas vinculadas; a integração completa de escalas manuais e texgen do GX ainda precisa ser feita. Não há promessa de equivalência bit a bit em todas as coordenadas extremas e todos os expoentes de matrizes indiretas: o shader usa floats para transportar valores inteiros.
- Os menus/previews existentes têm seu próprio caminho de renderização. A presença do combiner no backend GX não significa que todo o renderer original do HSD já o esteja utilizando.
- Os testes de Battlefield são previews de cenário. Continuam registrando callbacks de eventos de cenário ainda não implementados; não são uma partida.
- Fighter_Create e o runtime da luta continuam sem link completo. Não houve criação de Fighter original nem primeiro frame de gameplay nesta revisão.
- Otimização avançada e validação no Xbox 360 real continuam posteriores. Não foram acrescentados stubs ou `/FORCE` para esconder dependências.

Referências de semântica: o SDK original preservado na base e os arquivos primários [UberShaderPixel.cpp](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/UberShaderPixel.cpp) e [PixelShaderManager.cpp](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/PixelShaderManager.cpp) do Dolphin. Os corpos originais reutilizados são identificados separadamente no manifesto; o backend nativo é a tradução para o XDK.
