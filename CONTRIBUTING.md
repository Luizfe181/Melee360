# Como ajudar no Melee360

O projeto precisa de ajuda principalmente na camada GX, compatibilidade de áudio e preparação do build. Você pode contribuir com código, diagnóstico, documentação ou testes. Não é necessário trabalhar em tudo de uma vez.

## Comece por uma tarefa pequena

Abra uma issue descrevendo qual caminho pretende investigar, leia o relatório indicado e faça uma alteração isolada. Inclua o comportamento atual, a evidência do problema, a mudança proposta e como vai validar. Evite misturar otimização de renderer, gameplay e áudio no mesmo PR.

| Tarefa | Onde começar | Resultado útil / critério de aceitação |
| --- | --- | --- |
| Reduzir trabalho repetido de texgen | src/gx_texgen_state.inc, gx_texgen_api.inc e gx_texgen_probe.inc | Preservar UVs de entrada e dependências entre coordenadas geradas; cobrir múltiplas unidades, matrizes, normalização e bump; comparar pixels e medir. |
| Investigar buffers de vértices nativos | diagnostics/experiments/gx-native-ring-unvalidated.cpp e docs/gx-rewrite-20261005.md | Reproduzir a falha do probe de alpha, identificar causa e passar pelo mesmo probe. O tempo menor do caminho incorreto não conta como ganho. |
| Confirmar transformação compartilhada | src/gx_transform.c, tests/transform_host.c e docs/gx-shared-eye-20261005.md | Repetir comparação antes/novo/depois; verificar resultados exatos, capturas e estabilidade em execução ampliada. |
| Revisar lifetime do cache de texturas | src/gx_texture_cache.inc e docs/port-review-20261004.md | Mapear todos os owners/bindings e recursos GPU em voo antes de propor eviction. Preservar mutações RAM, mips e paletas. |
| Completar modos de áudio | src/ax_pcm_consumer.c e docs/symbol-completion-plan.md | Selecionar um modo pendente e adicionar vetores de referência, histórico/continuidade e reprodução verificável. Não usar funções vazias. |
| Tornar o build reproduzível | build.ps1, compile-gameplay.ps1, geradores e README.md | Centralizar caminhos locais e documentar dependências; testar em clone limpo sem incluir assets/XDK no Git. |
| Melhorar documentação | docs/decomp, relatórios de cada área | Corrigir links absolutos, separar estado histórico de estado atual e documentar limites com referência ao código. |
| Testar Xenia ou Xbox real | README.md e relatórios dos testes | Informar commit, flags, cenário, versões/configuração e resultados. Não comparar modos com fighters visíveis e invisíveis como se fossem iguais. |

Os caminhos da tabela são relativos a `outputs/Melee360`.

## Preparar e trabalhar

1. Faça um fork e clone o repositório.
2. Leia o [README](README.md), especialmente as limitações da reconstrução. Prepare o checkout original em work/melee-base no commit documentado e os arquivos locais exigidos pelo build.
3. Crie uma branch para uma tarefa, por exemplo `fix/texgen-inputs`.
4. Preserve o checkout original. Adapte a fronteira Melee360, registre a origem dos corpos extraídos e mantenha geradores sincronizados com as mudanças em código gerado.
5. Faça um PR pequeno com explicação, arquivos alterados, testes executados e limites conhecidos.

Ainda não há um fluxo completo de build limpo validado nem CI que substitua o XDK local. Se não conseguir compilar, contribua com o erro completo em texto e uma descrição do ambiente, sem anexar SDK, jogo ou dados pessoais.

## Regras de compatibilidade

- Preservar gameplay, física, AI, RNG e state machines originais. Alteração nesses caminhos exige um bug comprovado e uma reprodução.
- Manter a arquitetura Melee/HSD → API GX → tradução Melee360 → Xbox nativo.
- Não introduzir stubs, /FORCE, ausência silenciosa de funcionalidade ou símbolos duplicados para fazer a auditoria passar.
- Não remover probes ou referência anterior antes de validar o substituto.
- Não usar um endereço de asset/lista como única chave de cache: dados e matrizes podem mudar.
- Não tratar zero pendências de link como equivalência funcional do jogo inteiro.

## Como validar uma mudança

Escolha testes que exercitem o contrato alterado, não apenas a implementação. Compilação, host, Xenia e hardware real são etapas distintas; informe quais foram executadas.

Para renderer, use probes da área e uma cena reproduzível. Compare capturas internas equivalentes; preservar um ou dois frames é útil, mas não certifica todos os modos. Para áudio, use vetores conhecidos, histórico e continuidade; mantenha saída silenciada nos testes automáticos quando necessário e registre separadamente a validação auditiva.

Para performance, compare a mesma candidata com referência → alteração → referência. Mantenha cenário/flags/configuração, não compile durante a medição e faça repetições. Informe ms/frame, contagens, variação das referências e regressões. Tempos CPU incluem esperas GPU e não são timestamps GPU. Não somar tempos aninhados nem extrapolar ganhos do Xenia para Xbox.

Scripts existentes de referência:

- outputs/Melee360/verify-gx-transform.ps1
- outputs/Melee360/verify-xenia.ps1
- outputs/Melee360/verify-original-bootstrap.ps1
- outputs/Melee360/diagnostics/run_gx_shared_eye.ps1
- outputs/Melee360/diagnostics/run_gx_shared_eye_regression.ps1

Revise os scripts antes de executar: alguns exigem entradas locais e montam um pacote de diagnóstico. Use dados de teste separados e preserve saves/builds usados pelo jogador. Os scripts recentes restauram a XEX scratch e limpam suas próprias flags.

## O que enviar no PR

Descreva problema e comportamento resultante, decisão MANTER/ADAPTAR/MANTER A TRADUÇÃO, alteração mínima, testes, ganho observado e limites. Para otimização, inclua o cenário e as duas referências. Um PR sem acesso a testes XDK pode ser apresentado como proposta não validada; não afirmar que está pronto para execução.

Não inclua imagens de disco, DOL, DAT/USD, músicas, vídeos, fontes extraídas, saves, pacote RGH, XEX, SDK, builds ou logs com informações pessoais. A .gitignore ajuda, mas confira `git diff --cached --name-only` antes de enviar. Logs necessários podem ser resumidos/sanitizados em texto na issue.

## Sem XDK?

Você pode revisar contratos e estado no código, escrever casos de teste, analisar relatórios, melhorar os geradores/caminhos, corrigir documentação ou testar uma build própria já preparada. Informe claramente o que não pôde validar. Não é necessário obter ou compartilhar o SDK para contribuir com essas tarefas.