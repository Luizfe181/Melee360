# OS arena — implementação parcial

Arena própria de 8 MiB, separada do heap HSD de 64 MiB; inicialização preguiçosa com alinhamento de 32 bytes. OSGet/SetArenaLo/Hi e OSAllocFromArenaLo/Hi trabalham sobre memória real. Alocações exigem alinhamento potência de dois, verificam overflow e limites; falhas retornam NULL e preservam os limites. Setters fora do bloco reservado são ignorados. Essa validação é uma adaptação defensiva: não reproduz a possibilidade de apontar a arena original para endereços arbitrários.

O probe reserva pelas duas extremidades, escreve bytes, verifica alinhamento/overflow e restaura os limites sem ocupar memória para o jogo. O teste host também verifica esgotamento e setters inválidos. Não implementa OSInit completo nem anuncia 8 MiB como memória física do GameCube. O inicializador HSD original ainda precisa ser conectado; a arena não cria gameplay automaticamente.

A correção anterior de reuso de shaders/texturas do seletor e hashes cacheados foi mantida. Há 8 MiB adicionais reservados ao iniciar; medir o orçamento completo no console continua necessário.

Verificação final: pacote Release retail gerado; Xenia passou probe da arena, confirmação/cancelamento CSS e retorno ao título. Auditoria: 205 símbolos, 544 referências, zero duplicatas. A base original continua sem modificações. O desempenho desta revisão ainda requer validação física.
