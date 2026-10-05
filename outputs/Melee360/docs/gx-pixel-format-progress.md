# GXSetPixelFmt: formatos iniciais do backend Xbox

Implementada a traducao de GXSetPixelFmt para RGB8_Z24 e Z24, com depth linear. A funcao verifica os render targets reais do dispositivo: cor A8R8G8B8 (linear/sRGB) e depth D24S8, com dimensoes iguais. Nao cria um novo framebuffer nem muda o framebuffer dos previews.

RGB8_Z24 aplica mascara RGB=7; escrita alpha permanece excluida mesmo depois de GXSetAlphaUpdate(true). Z24 aplica mascara zero, mantendo o processamento de depth configurado por GXSetZMode. GXSetColorUpdate/GXSetAlphaUpdate agora combinam a intencao do caller com a mascara do formato. A chamada e proibida dentro de GXBegin.

RGBA6, RGB565/Z16, formatos Y/U/V e depth comprimido ainda sao recusados por assert; nao sao mapeados silenciosamente. Este e suporte parcial da API, nao todo EFB original. Os caminhos com destination-alpha blending e os formatos quantizados ainda exigem validacao dedicada antes de declarar equivalencia completa. GXSetFieldMode ainda nao foi implementado.

## Verificacao

Build XDK: logs/gx-pixel-format-build.txt.
Probe Xenia: valida targets, troca RGB8/depth-only, combinacao das mascaras apos chamadas de ColorUpdate/AlphaUpdate e restaura o estado anterior. Teste de estado do dispositivo; nao e comparacao de screenshots ou prova de fidelidade de todas as operacoes EFB.
Auditoria HSD ampliada: 110 ausencias, zero duplicacoes (logs/gx-pixel-format-hsd-audit.txt). GXSetPixelFmt deixou de faltar nesse caminho; GXSetFieldMode continua faltando.
Auditoria normal Mario/Link: permanece em 112 porque ainda exclui as rotinas HSD de inicializacao (logs/gx-pixel-format-baseline-audit.txt). Nenhum Fighter foi criado.
Validacao completa de Training: logs/gx-pixel-format-xenia.txt.

Training: a primeira execucao expirou em 180 segundos na CSS. A reexecucao passou sem alterar codigo/configuracao: logs/gx-pixel-format-xenia-recheck.txt. O timeout e intermitente; causa ainda nao demonstrada. A XEX validada foi copiada para package/RGH/Melee360/default.xex. Testes desta revisao foram feitos no Xenia, nao no hardware real.
