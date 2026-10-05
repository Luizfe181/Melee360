# Gameplay sem desenho: Mario jogador / Link CPU — 2026-10-02

## O que executa nesta build

19 rotinas isoladas do código original foram integradas: mpLineIntersection/H/V e 16 helpers de ftcommon.c para gravidade, velocidade terminal, queda rápida, aceleração/drift, limites de velocidade, contagem de pulos e desbloqueio da ECB. Seus corpos permanecem iguais ao upstream. Nomes são isolados com prefixo M360 para coexistir com a futura biblioteca completa; isso não resolve nem substitui símbolos do runtime completo. generate_logic_core.py gera o include e registra SHA256 dos fontes. A base original permanece sem alterações.

Os testes na inicialização executam os helpers sobre uma struct Fighter isolada com os atributos reais de PlMr.dat e PlLk.dat. Validam queda até a velocidade terminal e limite de drift para os dois personagens. Não executam Fighter_Create nem callbacks de estados, input, IA ou combate.

Adicionado um diagnóstico de varredura de ponto contra MapCollData usando a interseção dirigida original. Seleciona o primeiro contato, verifica bounds/índices/coordenadas e preserva saídas em erro. Em Battlefield testa varreduras verticais e cruzamentos normais às linhas de todos os quatro grupos estáticos: chão, teto, parede direita e parede esquerda. Não é o solver mpColl completo, não aplica resposta de contato a um Fighter e não representa hitboxes/hurtboxes, plataformas atravessáveis ou linhas dinâmicas.

Preparação Mario humano P1 / Link CPU nível 9 P2 em Battlefield, três vidas, sem equipes e sem itens, usando os helpers originais gm_SetupRulesDefaults, gm_SetupAllPlayerDefaults, gm_SetupHumanPlayer e gm_SetupCpuPlayer. Estrutura StartMeleeData fica separada do Training existente. Preparar dados de CPU não executa a IA. Nenhuma partida foi iniciada.

Não foi criado GX novo para gameplay. O desenho/menu atual permanece. A tela preta de partida não foi habilitada porque não há simulação completa executável atrás dela.

## Bloqueio real encontrado e corrigido

PlLk.dat possui dois externs: ItmLinkHShot_TopN_ACTION_Out_matanim_joint e ItmLinkHShot_TopN_ACTION_Out_shapeanim_joint. O loader antigo rejeitava qualquer arquivo com externs. lbArchive_InitializeDAT original inicializa suas cadeias com HSD_ArchiveGetExtern/HSD_ArchiveLocateExtern(..., NULL). O loader agora reproduz esse estado inicial com as APIs HSD originais, após validar as cadeias. NULL aqui é comportamento original de carregamento, não stub de função ou promessa de animação do hookshot funcionando. Atributos de Link carregam no Xenon e os slots iniciais dos externs são verificados como zero.

## Validação

Host: interseções dirigidas e rejeição na direção oposta, colinearidade, interseções H/V, primeiro contato entre dois pisos, movimento fora dos segmentos, erro de índice sem alterar saída, gravidade/terminal, drift nos dois sentidos, frenagem sem ultrapassar zero, contagem de pulos e unlock ECB. Configuração Mario/Link e independência do Training passaram. Fixture host-native valida cadeias de externs com duas referências e inicialização NULL pelo parser original; cinco assets reais passam a validação big-endian/corrupção/truncamento. O host não executa assets nativos big-endian.

Build Release/Compat XDK passou. Teste Xenia TrainingPreview verifica os novos probes nativos e regressão de navegação Training/CSS/SSS. Logs: headless-logic-host.txt, headless-archive-host.txt, headless-logic-build.txt e headless-logic-xenia.txt. Sem teste físico nesta etapa.

## Bloqueio da luta original

Auditoria -MarioLink: criação original dos dois Fighters ainda não liga, com 140 símbolos únicos ausentes e zero duplicatas. GX 55; AI/AX 35; FIO/MCC 18; OS/PAD/stack 12; VI 8; HSD 6; THP 6. Logs fighter-create-mario-link-summary.json/link.txt/missing.txt. Diagnóstico só de linker: não foi executado ou empacotado. Não houve stubs, /FORCE ou alteração de contagem para declarar uma luta pronta.

Mesmo sem chamar desenho, a criação original retém referências de classes HSD, modelos/bones/animadores, sombras, efeitos e inicialização da cena. A lógica de colisões de Fighter usa ECB e transformações do esqueleto; ocultar pixels não elimina esses requisitos. Próximo caminho: separar o registro de draw das classes/procs, preservando transforms e animação lógica; inicializar player/common data, mpLib e ciclo GObj com suas dependências reais; então chamar Fighter_Create dos dois e executar CPU/estados/solver original a 60 passos por segundo. Isso ainda é pendente, assim como ataques, dano, stocks e KOs em execução.

Revisao seguinte: 4 dependencias foram resolvidas, restam 136; veja mario-link-dependencies-progress.md. As listas fighter-create-mario-link-* agora refletem essa nova auditoria.
