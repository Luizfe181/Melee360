# GX primitivas diretas — subconjunto

GXBegin/GXClearVtxDesc/GXSetVtxDesc/GXSetVtxAttrFmt/GXPosition2f32/GXPosition3f32/GXColor3u8/GXColor4u8 implementados para listas de triângulos, posição float XY/XYZ e cor direta RGB8/RGBA8. A sequência aceita posição seguida de cor quando ativada; com posição apenas usa branco. Matriz corrente/projeção do banco novo produzem clip Xbox. Um draw real usa os shaders pré-compilados do port e textura branca. Não há função vazia de desenho.

O probe carrega matriz/projeção, define formatos, envia três vértices e fecha com GXEnd do header original (DEBUG ativo). A submissão ocorre quando o número esperado de vértices está completo; o guard __GXinBegin permanece ativo até GXEnd. As cenas atuais seguem pelo renderer direto anterior; o triângulo de teste é sobrescrito pela intro e não representa gameplay.

Limites explícitos: listas de triângulos apenas, sem strip/fan/quads/linhas; sem arrays/índices, texturas/UV/normais nesse caminho, múltiplos canais, TEV ou display lists via GXCallDisplayList. Esses casos são rejeitados, não tratados como desenhados. Inputs devem seguir os formatos e estar finitos. O bloco não torna o renderer GX completo. O port ainda usa DrawPrimitiveUP e não implementa FIFO GameCube.

Os recursos de shader/declaração/texture white persistem até o encerramento. O teste integra seis funções anteriores de transformação ao caminho de submissão GPU. A verificação de sucesso de DrawPrimitiveUP não é comparação visual independente da imagem nem medição no console físico.

Verificação: probe de submissão GPU passou no Xenia. O teste CSS percorreu confirmação/cancelamento e retornou ao menu VS, mas não concluiu retorno ao título no limite de 90 segundos; essa verificação completa não passou. Auditoria 179 símbolos/368 referências/zero duplicatas. Build retail atualizada. O primeiro teste falhou no probe; a configuração DEBUG de GXEnd foi ativada explicitamente e a inicialização/probe foram separados para diagnóstico. Os limites de cobertura permanecem os descritos acima.
