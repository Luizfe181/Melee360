# AXFX Reverb Hi — 2026-10-02

Implementados AXFXReverbHiInit, Shutdown, Settings e Callback. Tradução escalar de HandleReverb e DoCrossTalk em libs/dolphin/src/dolphin/axfx/reverb_hi.c. Três combs por canal com atrasos 1789/1999/2333; três allpasses por canal com 433/149 e 47 (left), 73 (right), 67 (surround). Coeficientes powf originais, 32 kHz, blocos de 160 amostras, ganho wet=.6*mix, dry=.6-wet e filtro .3 + damping*estado. No Xbox usa o powf original já integrado; CRT pow somente no harness host.

DoCrossTalk é aplicado antes do reverb e preserva a assimetria presente no assembly: left=(1-cross)*L+cross*R; right=.6*(cross*L+(1-cross)*R), cross=.5*crosstalk. Conversão dessa etapa usa nearest/even, correspondente ao fctiw com arredondamento padrão. Saída do reverb trunca, correspondente a fctiwz. Valores fora do intervalo ou não finitos retornam inteiro indefinido LONG_MIN. Não se afirma identidade bit a bit com Gekko/FMA ou modos alternativos FPSCR.

Adaptações explícitas: predelay usa todos os N elementos com wrap seguro, incluindo N=1; ponteiro armazenado no membro correto da estrutura, ao invés do endereço de buffer usado pelo trecho assembly. Validação de parâmetros finitos; Settings e Init fazem alocação transacional e preservam o estado anterior em falha. Ownership de hooks capturado, Shutdown repetível. Suporta 16 efeitos registrados. Chamadas precisam ser serializadas pelo futuro mixer; ainda não há vozes AX/DSP completas e o efeito não está ligado à música dos menus.

Testes host passaram (verify-reverb-hi.ps1; logs/reverb-hi-host.txt): impulso durante 30 blocos, primeiro eco em 1789 com amplitude aproximadamente -22500 para impulso de 1 milhão, canais restantes em zero; predelay unitário desloca eco para 1790; falha na terceira alocação libera dois buffers parciais e mantém os antigos; troca de Settings libera 18 buffers; dry mix, bypass, tempo inválido, crosstalk/gain dos três canais e ownership de 21 buffers após mudar hooks. Shutdown repetido não libera novamente. Layout público verificado em 0x1E0 e long de 32 bits.

Build Release/Compat passou: logs/reverb-hi-build.txt. Auditoria Mario/Link: 131 -> 128 ausências únicas; três exports principais resolvidos, Settings também implementado mas não era ausência. Zero duplicatas, sem stubs ou /FORCE. Logs/reverb-hi-audit.txt. Original em work/melee-base preservado.

Ainda não há Fighter_Create executado, partida Mario/Link, solver ECB completo ou itens no mapa. Reverb Hi funcional não equivale a AX/DSP completo; as vozes, endereçamento ARAM, mixagem e callbacks do engine continuam bloqueios reais.

TrainingPreview passou no Xenia com o novo probe obrigatorio e regressao GX/audio/Training/CSS/SSS. Log logs/reverb-hi-xenia.txt. XEX validada copiada para package/RGH/Melee360/default.xex; SHA256 atualizado. Sem teste em console fisico nesta etapa.
