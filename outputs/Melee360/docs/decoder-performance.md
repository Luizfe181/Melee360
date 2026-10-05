# Otimização da intro

O usuário confirmou que a intro abriu no console físico, mas relatou lentidão. Isso confirma a reprodução física dessa build, não garante desempenho nem o boot original completo.

Mudanças nesta revisão `intro-AAN-optimized-1`:

- IDCT direta por matriz substituída por transformada escalada AA&N de duas passagens, com atalho para linhas sem coeficientes AC.
- Escalas incorporadas às tabelas de quantização; não se calculam cossenos por quadro.
- Remoção de floorf na saturação; conversão YCbCr→RGB em aritmética inteira com arredondamento.
- Log com identificador da revisão e medições acumuladas de decode e upload a cada cinco segundos. O tempo de upload inclui LockRect/cópia/UnlockRect; não mede separadamente tempo de GPU, leitura ou Present.

Validação: todos os 3036 quadros passaram no decoder de host. As quatro imagens comparadas com Pillow/libjpeg permaneceram com erro médio abaixo de um nível de cor por canal; diferença máxima inclui reconstrução distinta de crominância. Entradas truncadas e assinatura inválida continuam sendo rejeitadas. Veja logs/mth-decoder-comparison.json.

Benchmark de host: 200 decodes do quadro 900, 11,795 ms/quadro na execução registrada em logs/mth-host-benchmark.txt. Isso não é medição do Xbox nem uma comparação confiável de antes/depois. Não se afirma FPS físico ou fator de aceleração sem novo teste no console.

No console, buscar no log a revisão `intro-AAN-optimized-1` e as linhas `Intro perf:`. A média de decode e upload ajuda a decidir a próxima otimização. A revisão anterior do log enviada pelo usuário não identificava a build nem media esses tempos.

Esta implementação é baseada em parte no trabalho do Independent JPEG Group. O butterfly foi adaptado da implementação [jidctflt.c do libjpeg-turbo](https://github.com/libjpeg-turbo/libjpeg-turbo/blob/main/src/jidctflt.c), extraindo a transformação de oito pontos, incorporando escalas à quantização do MTH e usando saturação explícita. Condições de distribuição estão em third_party/ijg/README.ijg; o restante do parser/leitor/player continua próprio.
