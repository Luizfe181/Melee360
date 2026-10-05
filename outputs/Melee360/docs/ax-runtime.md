# Runtime AX nativo — 2026-10-03

O caminho auditado de criação Mario/Link agora liga com **zero símbolos ausentes e zero duplicados**. AXInit e AXRegisterCallback têm execução real. Isso não certifica o AX completo nem uma partida.

## Implementado

- Allocator, listas de prioridade, setters, studio e rings auxiliares do decomp preservados.
- Driver nativo 32 kHz, blocos de 160 samples, mistura das vozes ativas e saturação estéreo.
- Callback AX por bloco, troca e remoção, acionado pelo consumo real dos buffers AI/XAudio2.
- PCM8/PCM16 da ARAM e ADPCM com coeficientes, histórico, cabeçalhos e contexto de loop.
- SRC NONE e linear 16.16, fração persistente e interpolação com intermediários s64.
- AXQuit/AudioClose param o DMA e aguardam o worker. Quit dentro do próprio worker é rejeitado para impedir auto-join.

O backend consome PBs CPU diretamente e substitui a execução DSP por código nativo. Não executa microcode nem mailbox GameCube. A saída ainda não foi comparada bit a bit ou capturada contra Dolphin.

## Testado no Xenia

Vetores ADPCM positivos/negativos e histórico em loop; SRC 0,5 e interpolação de extremos; duas vozes em blocos contínuos; amostras geradas verificadas e SamplesPlayed real; callback trocado/removido; ADPCM em loop com SRC na saída AI; shutdown; SRC 4-tap interrompe o DMA explicitamente.

Logs: ax-live-build.txt, ax-live-training.txt e ax-live-sound.txt. Auditorias: ax-live-fighter-audit.txt e ax-live-hsd-audit.txt. As mensagens de log são serializadas entre threads; uma expiração anterior causada por mensagem truncada está preservada em ax-live-before-log-lock-training.txt.

## Próximos bloqueios

1. RGBA6 com blending/AA e copia filtrada: GXSetDither e o caminho basico RGBA6 agora estao implementados e testados; veja gx-rgba6-progress.md.
2. SRC de quatro taps, coeficientes e comportamento exato do DSP.
3. Updates AX por milissegundo, PB CPU/DSP, FIR, ITD, tipos especiais e rampas de mix.
4. Auxiliares/surround: alimentar buses, processar retornos e aplicá-los à mistura; callbacks/rings já existem.
5. Depop L/R agora aplicado e testado; completar depop aux/surround e validar o fim natural de voz (bootstrap-runtime-progress.md).
6. Bancos SSM originais, comparação de áudio e jitter/underruns no console.

Vozes que solicitam modos atualmente não suportados fazem o driver parar com erro explícito. Os testes usam vetores de controle; Fighter e gameplay não foram executados.

Pacote atualizado: package/RGH/Melee360/default.xex. SHA256: E5E00FA27913A45976FEB38435D3D371202EB814C52C9A60832C4B6533D3BD8B. Backup: work/default-before-ax-live.xex. Manifesto: logs/ax-live-package-verification.json.
