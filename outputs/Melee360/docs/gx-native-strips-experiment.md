# Experimento: faixas nativas — 2026-10-04

Testado envio direto GX_TRIANGLESTRIP como D3DPT_TRIANGLESTRIP, mantendo expansão para listas quando a emulação early-Z exigia processamento por triângulo. Mesma XEX, configuração cache 64 MiB, Xenia headless, Mario CPU/Link CPU, Battlefield, 180 frames.

Referência: lógica 3,083 + render 355,510 + present 0,342 = 358,935 ms/frame.
Experimento: lógica 2,910 + render 360,133 + present 0,337 = 363,380 ms/frame.
Resultado observado: 1,24% mais tempo por frame. Não houve benefício demonstrado. Não foi feita repetição estatística nem validação visual longa, pois o candidato foi rejeitado nessa primeira comparação. Amostras CPU, 203241 desenhos, 1367 uploads e 345 cópias coincidiram.

Código experimental preservado em diagnostics/experiments/gx-native-strips-rejected.inc; retirado do caminho ativo. XEX publicada permanece a revisão cache64, SHA256 1E0458D94556D1F4B2FAE880929BEBAE29039A775F44B89670641466D4E238A6. Scratch restaurado com essa mesma imagem. O binário em build/Release/Compat pertence ao experimento e precisa ser recompilado antes de uso.

Os perfis existentes medem render CPU wall time incluindo espera GPU. Eles não permitem atribuir todo o tempo restante ao shader ou ao upload. Próxima investigação: separar tempo de montagem/transformação de vértices, submissão e esperas/execução GPU, antes de escolher outra alteração.
