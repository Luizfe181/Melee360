# Ligacao inicial GXLoadTexObj ao Xbox

Implementado GXLoadTexObj para TEXMAP0 sem mipmaps/paleta, usando descritores inicializados pelo GXInitTexObj original. O decoder existente transforma I4/I8/IA4/IA8/RGB565/RGB5A3/RGBA8/CMPR em pixels ARGB, que sao enviados para uma textura D3D linear. O shader de desenho GX agora usa essa textura em vez da branca padrao quando ha uma carga ativa. Cada chamada refaz upload; cache/performance ficam para uma etapa posterior.

GXInitTexObj ganhou uma unica adaptacao depois do corpo original: captura do ponteiro CPU completo da imagem. O descritor GameCube grava somente bits de endereco fisico, insuficientes para recuperar um ponteiro Xenon arbitrario. O codigo base permaneceu intacto; a mudanca existe apenas no fonte gerado do port e em seu generator. Proveniencia e adaptacao em logs/portable-gx-provenance.json.

Wrap clamp/repeat/mirror e filtros nearest/linear sem mipmaps sao aplicados ao sampler. Mipmaps, CI/paletas, unidades diferentes de TEXMAP0 e anisotropia nao suportada sao recusados. Copias de descritores sem registro de imagem e alteracoes posteriores via GXInitTexObjData ainda precisam do contrato de ponteiros; nao sao declaradas implementadas. O shader atual ainda nao e TEV completo. Os previews de menus usam outro caminho de render, portanto esta etapa nao promete mudanca visual neles.

## Testes

CPU host: logs/gx-texture-binding-host.txt, passou sem alterar resultados dos descritores originais; o harness captura as duas chamadas de registro e confere o ponteiro completo. Build XDK: logs/gx-texture-binding-build.txt.
GPU Xenia: seis draws (3 wrap modes x 2 opacidades) com RGBA8 tiled e alpha compare. Queries de oclusao confirmam que alpha zero nao produz pixels e alpha 255 produz, demonstrando amostragem da textura carregada. Sampler address U/V e conferido nos tres modos; o teste nao prova todos os casos de amostragem fora do dominio nem todos os formatos na GPU. Estado de sampler, textura e alpha e restaurado apos o probe.
Auditoria normal: 111 ausencias; ampliada HSD: 109. Ambas zero duplicacoes, linked=false, executed=false. Logs gx-texture-binding-baseline-audit.txt e gx-texture-binding-hsd-audit.txt. Nao houve criacao de Fighter.

## GXSetFieldMode

Segue pendente. A analise do fonte GXPixel.c confirma escrita do bit de proporcao LPSize e registrador de field mode. A referencia Dolphin BPMemory identifica esses contratos como ajuste de LOD e proporcao de linhas/pontos, e nao como simples descarte de linhas alternadas. A implementacao exige consumidores correspondentes antes de poder declarar suporte.
Referencia primaria: https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/BPMemory.h (consultada em 2026-10-02). Nenhum codigo Dolphin foi copiado para o port.

TrainingPreview inicial expirou em 180 segundos no menu de 1 jogador (logs/gx-texture-binding-xenia.txt). Os probes GPU de textura tinham passado antes desse ponto. Reexecucao em logs/gx-texture-binding-xenia-recheck.txt; timeout nao foi corrigido ou atribuido a uma causa nesta revisao.

A reexecucao de Training passou: CSS, selecao de mapas, rejeicao de outro mapa, preparo Battlefield e retorno ao menu. XEX validada copiada para package/RGH/Melee360/default.xex. Esta build foi testada no Xenia; nenhum teste novo no console real.
