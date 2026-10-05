# GXColor1u16 — 2026-10-02

Formato CLR0 RGB/RGB565 agora suportado no backend direto. GXColor1u16 expande
os canais 5/6/5 bits para 8 bits, define alpha=1 e preserva a espera por TEX0
quando ele está habilitado. O vértice segue pela transformação e GPU anteriores.
Não foi implementada leitura de cores indexadas (GXColor1x8/GXColor1x16).

Probe: vermelho f800, verde 07e0, azul 001f; verifica canais normalizados,
envia triângulo à GPU e restaura RGBA8 antes dos testes de topologias/UV.
Build XDK: logs/gx-rgb565-build.txt. Regressão: logs/gx-rgb565-xenia.txt.
Auditoria Fighter: 146 símbolos, zero duplicatas, logs/gx-rgb565-audit.txt.

Não foram finalizados todos os 147 símbolos da solicitação. Não há criação
de Fighter nem frame de gameplay. O callback de reverb_std.c original é assembly
Metrowerks; suas rotinas C não tornam o efeito completo sem tradução e testes
do processamento. Nenhum callback de áudio foi substituído por no-op.

Regressão Training/CSS/Battlefield no Xenia concluída com exit 0. Probe RGB565 e probes anteriores passaram. Falta teste em Xbox 360 físico.
