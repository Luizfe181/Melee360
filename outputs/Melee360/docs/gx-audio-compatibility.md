# Compatibilidade GX e AX/DSP — 2026-10-02

Escopo autorizado: toda a tradução funcional de renderização e áudio para Xbox
360. Otimização fica para depois; Mario/Battlefield são casos de teste, não
limites da implementação. Não declarar funções resolvidas por assinatura ou
por presença de um símbolo sem comportamento correspondente.

## Incremento atual

GXTexCoord2f32 e GXTexCoord2u8 agora escrevem TEX0/ST no vértice enviado à GPU.
U8 aplica 2^-frac. O estado do vértice espera posição, cor opcional e coordenada
de textura opcional na ordem GX; só então conclui o vértice. Não permite iniciar
outra posição antes de concluir os atributos. GXClearVtxDesc limpa TEX0.

Probes: triângulos F32 e U8 sem TEX0, seguidos de TEX0 U8/fracionário e F32,
com verificação de coordenadas e conclusão do estado. O backend direto ainda
usa textura branca: o teste verifica atributos e submissão, não prova GXLoadTexObj,
TLUT ou TEV. Normal, índices, múltiplas UVs e display lists ainda faltam.

Build XDK: logs/gx-uv-build.txt. Regressão Xenia: logs/gx-uv-xenia.txt.
Auditoria Fighter: 147 pendentes, zero duplicatas, logs/gx-uv-fighter-audit.txt.
Não há primeiro frame de gameplay e nenhum novo serviço AX foi implementado
neste incremento. A reprodução HPS/XAudio anterior permanece parcial.

## Dependências seguintes

Render: arrays/índices e display lists; normais/matrizes/iluminação;
texturas/TLUT; geração de coordenadas; combinações TEV e indirect;
alpha/fog/cópias e estado VI. Cada estado precisa de consumidor no backend,
não apenas armazenamento que reduza a contagem no linker.

Áudio: gestão de vozes AX, endereçamento ARAM e formatos PCM/DSP;
ADPCM e loop history; SRC/ratio; envelopes/mix/ITD; callbacks e auxiliares;
chorus/reverb originais traduzidos do assembly. Integração ao XAudio com
blocos e sincronização coerentes. Testes de impulso, loop, pitch, ganho,
liberação e callbacks antes de conectar synth/SFX originais.

Os dados e a base original são preservados. Falta validar estas mudanças em
Xbox 360 físico; testes Xenia não comprovam desempenho em hardware.

Regressão Training/CSS/Battlefield no Xenia concluída com exit 0. Os quatro probes de atributos e os demais probes de runtime passaram.
