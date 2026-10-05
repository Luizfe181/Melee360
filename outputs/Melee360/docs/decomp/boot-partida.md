# Boot e primeiro frame original

## Boot original observado

Fonte: src/melee/gm/gmmain.c:130. Ordem relevante: OSInit, VIInit, DVDInit, PADInit, CARDInit, OSInitAlarm; configura parâmetros HSD; aloca XFB/FIFO; GXInit e HSD_InitComponent; áudio e callbacks de apresentação; serviços lbMemory/lbHeap/lbDvd/lbArq/lbCard/lbSnap; dados globais gm, vídeos, SIS; modo debug opcional; habilita itens; inicia scene manager gm_801A4510.

O port usa seu próprio main Xbox e inicialização parcial. Importar o main original inteiro agora executaria suposições de framebuffer/FIFO, memória e vídeo ainda não suportadas. A auditoria não demonstra que esse boot passou.

## Fighter_Create

Fonte: src/melee/ft/fighter.c:848. Cria GObj e GX link; aloca Fighter e backup de atributos; registra destructor; carrega dados do personagem, efeitos e costume; prepara joints/parts, animação e estado comum; obtém posição de bones; executa OnLoad do personagem; inicializa colisão e camera box; prepara shadow; registra os processos e executa Fighter_Spawn.

Consequência: omitir desenho não elimina automaticamente HSD. Joints e animações também fornecem posições para colisões, acessórios e gameplay. Tabelas por personagem podem reter referências a itens/efeitos e outros modos.

## Processos registrados e prioridades

| Prioridade | Processo |
|---:|---|
| 0 | Fighter_procHitlag |
| 1 | Fighter_procAnim |
| 2 | Fighter_procCpu |
| 3 | Fighter_procInput |
| 4 | Fighter_procUpdate |
| 6 | Fighter_procMap |
| 7 | Fighter_procIK |
| 8 | Fighter_procAccessory |
| 9 | Fighter_procCollPos |
| 12 | Fighter_procGrabColl |
| 13 | Fighter_procAttackColl |
| 14 | Fighter_procCollResolve |
| 16 | Fighter_procDynamics |
| 18 | Fighter_procCamera |
| 22 | Fighter_procPlayer |

Ordem extraída diretamente de Fighter_Create. Scheduler completo possui outros objetos/prioridades; esta tabela não descreve todo o frame da partida. Fighter_procCpu chama ftCo_800B3900 para CPU ativa; procMap e resolução de combate têm estados e callbacks adicionais.

## O que o ensaio atual realmente faz

O entry diagnóstico em diagnostics/mario_link_link_entry.c chama configuração Mario humano/Link CPU, Fighter_FirstInitialize e duas Fighter_Create. Ele é usado para link, não incluído/executado como partida na XEX. Os probes nativos aplicam algumas rotinas de gravidade/interseção a estruturas/dados isolados. Isso não equivale a scheduler, player runtime, IA ou estado de combate original.

Critério para o primeiro frame: boot mínimo consistente, dados comuns/player/cenário carregados, Fighter_Create retornar objeto válido, callbacks originais de um tick rodarem na ordem, posição/ECB/estado inspecionáveis, sem stubs e sem reinitializar heap vivo. Só depois validar controle, movimento, pulo e resposta ao mapa.
