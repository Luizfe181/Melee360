# GXPosition2u8 — 2026-10-02

Implementação real no backend direto: formato POS XY/U8, escala 2^-frac,
transformação pela matriz/projeção GX e envio à GPU Xbox. Outros formatos e
atributos ainda são rejeitados quando não implementados; não viram no-ops.

O probe desenha um triângulo F32 e outro U8 consecutivamente e verifica as
coordenadas transformadas de 1 com frac=1 (0.5). Encontrou um problema no
GXEnd inline entre unidades compiladas com diferentes DEBUG flags; o teste
agora usa encerramento local com verificação de contagem e estado do backend.
Isso não resolve o encaminhamento completo de display lists do HSD.

Build XDK concluída. O probe GPU passou no Xenia; a regressão completa está
em logs/gx-u8-xenia.txt. Auditoria Fighter: 149 símbolos pendentes e zero
duplicatas, logs/gx-u8-fighter-audit.txt. Não há criação de Fighter nem frame
de gameplay. O restante de GX/TEV, AX/DSP, VI e HSD permanece pendente.

Os fontes originais de chorus e reverb existem, mas seus callbacks têm assembly
Metrowerks: inclusão direta não é implementação compatível com XDK. Não foram
substituídos por stubs. A base original continua sem alterações.

A primeira regressão completa excedeu 90 s na seleção de Mario, sem assert. Repetida com prazo de 180 s para Training, passou (processo exit 0): logs/gx-u8-xenia-retry.txt. Auditoria completa: 170 símbolos/353 referências; Fighter: 149. Nenhum dos demais 149 foi declarado resolvido.
