# UVs indexadas GX — 2026-10-02

GXTexCoord1x8/GXTexCoord1x16 buscam TEX0/ST no array registrado por GXSetArray.
Suportam U8 fracionário e F32 no byte order nativo big endian do Xbox, com stride
explícito. F32 é lido por memcpy para não exigir alinhamento do registro.
O estado aguarda posição e cor antes da UV e só então conclui o vértice.

Probes GPU: U8 com padding/stride 4 e frac=1; F32 com stride 12 e índices
256–258. Verifica coordenadas normalizadas e encerra os arrays temporários.
Logs: gx-uv-index-build.txt, gx-uv-index-xenia.txt e gx-uv-index-audit.txt.
Auditoria Fighter: 141 símbolos ausentes, zero duplicatas.

GXSetArray ainda parcial: CLR0 e TEX0. Outras UVs, atributos indexados de
posição/normal, geração de coordenadas e display lists ainda faltam.
O desenho direto continua com textura branca; esses testes não validam
GXLoadTexObj, TLUT ou TEV. Nenhum novo serviço AX foi implementado.
Sem Fighter original executando; base original preservada.

Regressão Training/CSS/Battlefield concluída no Xenia com exit 0. Validação em console físico pendente.
