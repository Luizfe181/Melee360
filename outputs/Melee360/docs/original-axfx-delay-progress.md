# AXFX delay original — 2026-10-02

Revisão: original-axfx-delay-1.

## Integração

`generate-axfx.ps1` extrai sem alteração AXFXDelayCallback de
libs/dolphin/src/dolphin/axfx/delay.c e AXFXSetHooks de axfx.c.
`compat/generated/axfx_original.inc` registra os SHA256 das duas fontes.
A base work/melee-base permanece intacta.

`src/axfx_delay.c` compila os blocos originais. O callback público valida
estado/ponteiros antes de chamar o processamento original. A infraestrutura
AXFXDelayInit, AXFXDelaySettings, AXFXDelayShutdown e os alocadores padrão
são adaptações do port: conservam fórmulas originais de tamanho/gain/feedback,
mas validam parâmetros e tratam falha de memória sem abortar o jogo.

- Blocos de 160 amostras, três canais: esquerda, direita e surround.
- Delay aceito de 6 a 5000 ms; feedback/output de 0 a 100.
- Até 16 instâncias registradas. O chamador deve serializar callbacks/settings.
- Init exige objeto novo ou já pertencente a esta implementação; repetir Init
  reaplica configurações. Não aceita buffers externos como propriedade AXFX.
- Settings aloca os três buffers antes de liberar os antigos; falha preserva
  o efeito ativo. Mudança dos hooks não altera o liberador dos buffers antigos.
- Shutdown é repetível, zera ponteiros e evita liberação duplicada.
- No Xbox os defaults usam o heap HSD existente. No teste host usam malloc.
- Não se adicionou saturação nem nova taxa de amostragem ao callback original.
  A representação numérica original continua sendo o contrato do mixer AX.

## Validação e resultado

`verify-axfx.ps1`: impulso com delays diferentes nos três canais, ausência de
saída antecipada, eco/feedback, retorno circular, limpeza em reconfiguração,
falha na terceira alocação, parâmetros inválidos, hooks e shutdown repetido.
O mesmo probe executa no boot XDK. Logs: axfx-host.txt, axfx-xdk-build.txt,
axfx-xenia.txt. verify-xenia.ps1 exige o sucesso do novo probe e valida os
menus/troféus existentes no percurso -TrophiesPreview.

Audit completo com runtime: 179 -> 175 símbolos ausentes, 364 referências
restantes e zero definições duplicadas. Ele ainda NÃO gera uma build de
partida; o XEX distribuído é a build funcional de menus/diagnósticos.

## Ainda falta

Este efeito está ligado ao executável e testado, mas ainda não está conectado
à música XAudio dos menus. Não altera deliberadamente o áudio do menu para
simular integração AX. Faltam mixer e vozes AX, callbacks AUX, efeitos SSM,
roteamento original de efeitos e música nas partidas. Chorus/reverb originais
contêm assembly Gekko e exigem tradução e testes próprios. Gameplay ainda
não executa uma partida. Esta revisão não altera o conteúdo das telas.

O primeiro teste Xenia expirou por perda de mensagens de boot: o verificador
abria o log sem FileShare.Write, bloqueando escritas momentaneamente. A leitura
agora usa FileShare.ReadWrite; a segunda execu��o verificou tamb�m o probe AXFX.
