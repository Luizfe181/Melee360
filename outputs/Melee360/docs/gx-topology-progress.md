# Primitivas GX — 2026-10-02

GXBegin agora aceita TRIANGLES, QUADS, TRIANGLESTRIP e TRIANGLEFAN no backend
direto. Quads usam (0,1,2)/(0,2,3); strips alternam a ordem dos dois primeiros
índices; fans mantêm o vértice inicial. A conversão preserva todos os atributos
do vértice e envia triangle lists ao Direct3D Xbox. Contagens inválidas são
rejeitadas; outras primitivas ainda não implementadas não viram no-ops.

O probe cria cada topologia de quatro vértices e verifica seis vértices de saída,
incluindo a ordem do segundo triângulo. Submete os três desenhos à GPU e depois
executa os probes anteriores de posições e UVs. Não é um teste visual completo
de materiais nem uma implementação de GXCallDisplayList.

Build XDK: logs/gx-topology-build.txt. Teste e regressão Training/CSS/Battlefield:
logs/gx-topology-xenia.txt. A validação é no Xenia, sem teste em console físico.
A contagem anterior de 147 símbolos do caminho Fighter não muda: foram ampliadas
funções já presentes. Nenhum Fighter foi criado e nenhum novo serviço AX/DSP
foi implementado nesta revisão. Otimização continua fora do incremento.

A regressão completa terminou com exit 0, sem ASSERT/FAILED; houve retorno ao menu principal após Training/CSS/Battlefield.
