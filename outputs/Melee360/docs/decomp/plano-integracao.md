# Plano de integração por marcos

## 1. Estabelecer uma inicialização única HSD

Revisar initialize.c, hsd_memory.c, os_arena.c, objalloc e class registry como um bloco. Definir quem cria/destrói heap e arena; preservar classes/pools vivos. Executar init apenas uma vez, com prova de alocação/liberação e bounds. Resolver getters/init originais junto com os consumidores reais; não criar aliases para contornar ownership.

## 2. Completar os contratos gráficos exigidos pela criação

Rastrear o caminho de material/joint em Fighter_Create e OnLoad Mario. Implementar normais/luzes, textura/TLUT e TEV por grupos com consumidor e teste de pixels. Separar estado usado só no desenho de estado necessário a joints/animation. Não substituir material completo por shader fictício para declarar original renderer concluído.

## 3. Criar o primeiro Fighter com dados comuns reais

Preparar gm/player, PlCo/Mario/costume e stage; init original; Fighter_Create Mario. Capturar falhas por ordem real de execução. Primeiro provar retorno, classe, joints, atributos, motion state e ECB. A lista de 112 é dependência de link: novas falhas de dados/init podem surgir após resolver o link.

## 4. Tick original em Battlefield

Carregar stage/collision e registrar processos originais. Avançar exatamente um tick; depois centenas de ticks com player parado. Testar posição finita, velocidade, contato chão, ownership e frame de animação. Sem render completo, logs/instrumentação podem demonstrar tick; o gameplay não deve ser refeito por aproximação.

## 5. Controle e colisão

Input original -> estados Wait/Walk/Jump -> física -> solver mp/ECB -> pose. Validar transições, salto, pouso, plataformas, bordas e paredes. Sweeps de pontos existentes ajudam testes geométricos, mas não substituem a resposta original.

## 6. Link CPU e combate

Adicionar segundo Fighter após Mario estável. Executar CPU original; validar hitboxes/hurtboxes, hitlag, damage, knockback, grab e KO. Medir determinismo de estado com input conhecido. Não atribuir compatibilidade geral a um duelo que usa poucas ações.

## 7. Itens e áudio AX

Itens exigem spawn original, tipo/dados, GObj, física, colisões com stage/Fighters, callbacks e cleanup. Começar por um item realmente usado pelo caminho Link/Mario e um drop de stage controlado; não ativar todos antes de validar lifetime. Implementar mixer AX em paralelo lógico ao runtime, com bancos/endereçamento/loop/SRC/AUX; testar vozes reais, não só setters. Tabelas it/kinds permitem ampliar depois do primeiro caso.

## Como acelerar com segurança

Trabalhar em contratos completos com seus consumidores, em vez de escolher export fácil apenas para baixar o contador. Agrupar headers/layouts, implementação e testes por subsistema. Usar a auditoria para localizar referências, mas priorizar trace do runtime. Não ampliar testes repetidos quando nada mudou; recompilar/testar os caminhos alterados e manter uma regressão de menus ao publicar.

Nenhuma porcentagem global: medir marcos verificáveis (init, create, tick, input, collision, combat, items, sound/render completos). Os próximos trabalhos de maior impacto são init HSD e estado/material GX necessário ao Fighter, depois voice engine AX. MCC/THP debug podem ser necessários ao link por retenção; investigar antes de tratá-los como primeira dependência runtime.
