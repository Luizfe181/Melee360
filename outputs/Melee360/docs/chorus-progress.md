# AXFX Chorus — 2026-10-02

Implementados AXFXChorusInit, Shutdown, Settings e Callback. Tradução escalar dos dois resamplers do_src1/do_src2 de libs/dolphin/src/dolphin/axfx/chorus.c. Tabela original de 512 coeficientes preservada em src/axfx_chorus_table.inc: 128 fases, quatro taps por saída. Cursor fracionário Q32, carry e avanço de 0/1/2 amostras; wrap 480 -> 0; histórico dos três taps salvo entre blocos. Saída trunca para long de 32 bits como fctiwz. Não se afirma igualdade bit a bit com fmadds Gekko.

Callback mantém o corpo original de cópia de 160 amostras por canal, rotação de três blocos, cálculo de pitch e alternância de sinal. Apenas os helpers assembly foram substituídos pelo resampler escalar. Buffer único de 0x1680 bytes contém três canais com 480 amostras cada, sem exigir que os buffers de entrada/saída sejam contíguos. A API transforma as amostras recebidas; não são funções vazias.

Adaptações: inicializa o buffer inteiro em zero; Init valida parâmetros e aloca antes de substituir o efeito existente; falha preserva o anterior; hooks de liberação são capturados por ownership; Shutdown repetível. Até 16 efeitos. Settings usa módulo normalizado para posição negativa da rotação em vez de wrap unsigned. Cálculo do pitch usa intermediário de 64 bits para evitar overflow do shift. Faixa atualmente suportada: baseDelay 5..15; period >=5; offset calculado <=65535, para os dois casos de pitchHi que o callback original suporta. Valores fora dessa faixa retornam erro, não são ignorados. Chamadas precisam ser serializadas pelo futuro mixer AX, que ainda não está integrado.

Teste host verify-chorus.ps1 passou: layout 0x9C, impulso com baseDelay=10/variation=0 e primeiro tap em amostra 160 aproximadamente -976, canais independentes, ring wrap entre seis blocos; falha de Init preserva buffer e não o libera; period=0 rejeitado preservando cursor; modulação fracionária variation=1 durante 40 blocos, ambos pitchHi 0/1 observados e posições sempre menores que 480; ownership após troca de hooks e Shutdown repetido. Logs chorus-host.txt. Build XDK Release/Compat passou: chorus-build.txt.

Auditoria Mario/Link: 128 -> 125 ausências únicas, zero duplicatas. Init/Shutdown/Callback resolvidos; Settings também implementado mas não era ausência. Log chorus-audit.txt. Sem stubs ou /FORCE; base original preservada.

Chorus ainda não está conectado às vozes/mixer AX nem à música dos menus. Não há Fighter_Create executado, partida, IA Link, colisão ECB completa ou spawn de itens. Esses continuam bloqueios reais; processamento de efeito não equivale a DSP/AX completo.

TrainingPreview passou no Xenia com probe chorus obrigatorio, demais probes de render/audio e percurso Training/CSS/SSS/retorno ao menu. Log chorus-xenia.txt. XEX validada atualizada no pacote e SHA256 renovado. Sem teste em hardware real nesta etapa.
