# Mipmaps, paletas e oito unidades GX

## Implementacao

GXLoadTexObj agora aceita TEXMAP0..7, mantendo imagem, descritor, dados de origem e sampler independentes. GXSetTevOrder seleciona a unidade amostrada pelo shader para o contrato inicial: somente TEVSTAGE0, TEXCOORD0 e COLOR0A0. Nenhuma combinacao ficticia de oito texturas foi adicionada. Outros estagios, coordenadas e canais continuam recusados; os 16 estagios TEV completos permanecem pendentes.

Mipmaps GX sao percorridos com o padding de tiles proprio de cada nivel, decodificados e enviados para niveis reais da textura Xbox. Foram adicionados filtros mip nearest/linear, min/mag, bias, limites de LOD fracionarios e estado de anisotropia 1/2/4. O shader GX passou a ps_3_0 para calcular LOD a partir de derivadas, aplicar bias e clamp antes da amostragem explicita. Nao se declara equivalencia bit a bit com o calculo GX de LOD, arredondamento/edge LOD ou anisotropia; bias_clamp ainda e recusado.

Texturas com mips usam XGSetTextureHeaderEx com XGHEADEREX_NONPACKED e memoria fisica propria para base e cadeia, alinhada em 4096. O upload usa XGTileTextureLevel e os limites reais obtidos de XGGetTextureLayout. O dono da textura retira bindings, aguarda GPU e libera header/memoria. A escolha evita depender do mip tail compartilhado para mips pequenos. Os testes iniciais com o layout compactado falharam ao amostrar mip 1; o ajuste de deslocamento sozinho nao resolveu. O layout nao compactado passou. Nao foi comprovado que a causa restante fosse exclusivamente um bug do Xenia.

GXLoadTlut implementa 20 nomes de paleta (16 TLUT e 4 BIGTLUT), com snapshot dos dados carregados. C4/C8/C14X2 usam IA8/RGB565/RGB5A3 e validam indices. Recarregar uma TLUT atualiza as texturas CI ja carregadas que usam seu nome, inclusive os mipmaps. Os dados indexados permanecem numa copia propria para esse reupload. A memoria TMEM sobreposta do GameCube nao e emulada: os nomes de paleta sao slots logicos independentes.

GXInitTlutObj recebeu a mesma adaptacao de ponteiro Xenon usada em GXInitTexObj, depois do corpo original. Fontes decomp preservados; proveniencia em logs/portable-gx-provenance.json. Descritores copiados sem registro e alteracoes via GXInitTexObjData ainda exigem integracao. Cache e otimizacao de reuploads ficam pendentes.

## Testes e evidencias

Build XDK: logs/gx-texture-expansion-build.txt.
Shaders: logs/gx-texture-expansion-shaders.txt.
CPU host: logs/gx-texture-expansion-host.txt, passou com captura do ponteiro/parametros da TLUT e preservacao dos descritores originais.

29 queries GPU Xenia verificaram:
- Oito slots carregados antes de desenhar, com selecao posterior e alpha alternado.
- As nove combinacoes C4/C8/C14X2 x IA8/RGB565/RGB5A3, incluindo indice 257.
- Quatro niveis de mip com opacidade alternada, amostrados por limites de LOD.
- Recarga de TLUT mudando alpha da textura ja ligada.
- Filtro mip linear, bias negativo e estado de anisotropia.
- LOD fracionario 0,5 e 0,25 com interpolacao entre mips.
- Mip C4 e recarga de sua paleta sem nova carga da imagem.

Os testes GPU usam alpha/oclusao; nao comprovam todas as cores, wrapping fora do dominio, projecao de coordenadas ou fidelidade completa dos filtros. Os probes restauram slots, samplers, LOD, alpha e registries anteriores.

O fluxo TrainingPreview verifica CSS, mapas, rejeicao de outro mapa, preparo das regras Battlefield e retorno ao menu, sem iniciar gameplay. Log final: logs/gx-texture-expansion-xenia-final.txt. As falhas iniciais de mip foram preservadas nos demais logs gx-texture-expansion-xenia*.txt.

Auditoria normal Mario/Link: 109 ausencias; ampliada HSD: 107. Zero duplicacoes; linked=false, executed=false. GXLoadTlut e GXSetTevOrder deixaram de estar ausentes; ambos tem os contratos parciais descritos acima. Nenhum Fighter foi criado.

## Pacote publicado

A XEX verificada no Xenia foi copiada para package/RGH/Melee360/default.xex. SHA-256: EBBD32B99078B5AC3C2C77EFE806E78D0B22B81800B4A241AF6C3B23AE28586B. A base work/melee-base permanece sem alterações. Esta revisão ainda não foi testada no console real.

## Atualizacao: troca da imagem

GXInitTexObjData foi integrado com seu corpo original e captura do ponteiro Xenon apos atualizar o descritor. Isso permite substituir a imagem de um objeto existente e carrega-la novamente com GXLoadTexObj, preservando formato, tamanho e nome da paleta. Nao altera automaticamente a textura que ja esta ligada sem nova carga GXLoadTexObj.

O teste CPU valida o endereco no descritor e a preservacao de tamanho/formato/TLUT. Dois novos testes GPU substituem a imagem por dados transparentes e depois opacos, verificando o resultado por oclusao. Total: 31 testes GPU aprovados, alem do fluxo TrainingPreview. Logs: gx-image-replacement-host.txt, gx-image-replacement-build.txt e gx-image-replacement-xenia.txt. Auditoria permanece 109/107: este export nao constava das ausencias daquele caminho.

Pacote RGH atualizado com a build verificada. SHA-256 atual: 96CD9D0647E4349F286A27D54AB7F59F33F9398076356C3EA030328A3C7B413F. Validacao de hardware desta atualizacao ainda pendente. O usuario informou ausencia de erros na revisao anterior, sem especificar a plataforma.

## Atualizacao: modos TEV predefinidos

GXSetTevOp agora traduz GX_MODULATE, GX_DECAL, GX_BLEND, GX_REPLACE e GX_PASSCLR no TEVSTAGE0. Equacoes derivadas de libs/dolphin/src/dolphin/gx/GXTev.c, preservando a base. Modulate multiplica textura/raster; Decal interpola RGB pelo alpha da textura e preserva alpha raster; Blend interpola raster/branco pelo RGB da textura e multiplica alpha; Replace usa textura; Pass Color usa raster. Estado enviado ao shader, restaurado apos os probes. Outros estagios sao recusados.

Dez novas queries GPU confrontam textura opaca/raster transparente e textura transparente/raster opaco nos cinco modos. Total 41 queries e fluxo TrainingPreview aprovados no Xenia. Esses testes verificam alpha, nao todas as cores/intermediarios. Calculo shader float: arredondamento inteiro GX e equivalencia bit a bit permanecem pendentes. Combiner geral, registros TEV e sequencias de 16 estagios ainda nao implementados; nao ha stubs para esses exports.

Logs: gx-tev-modes-shaders.txt, gx-tev-modes-build.txt, gx-tev-modes-xenia.txt, gx-tev-modes-audit.txt e gx-tev-modes-hsd-audit.txt. Auditoria normal: 108 pendencias, zero duplicacoes; Fighter continua sem link/execucao. Pacote RGH atualizado com XEX verificada, SHA-256 73825773BADA80372062E79DA6464F2DFA4F30E91291CD12493F0E572D38BBED. Hardware real ainda nao validado nesta revisao.
