# AX: controle original de vozes e buffers auxiliares — 2026-10-03

As duas auditorias de criação Mario/Link (com e sem inicialização HSD) passaram de **64 para 44 símbolos ausentes**, com **zero duplicações**. O link completo do Fighter continua falhando e não foi executado. Nenhum stub ou `/FORCE` foi acrescentado.

## Implementação

`diagnostics/generate_portable_ax.py` extrai os corpos originais de AXVPB.c, AXAlloc.c, AXCL.c e AXAux.c para `compat/generated/portable_ax.c`. `generate-portable-ax.ps1` reproduz a geração e está integrado em `build.ps1`. A base em `work/melee-base` foi preservada.

- Alocador original com 64 vozes, listas por prioridade, retirada pelo fim da lista, callbacks de roubo, liberação e reutilização.
- Parâmetros originais de estado, mix, ITD, envelope/volume, endereços, loop, ADPCM e SRC. Máscaras de sincronização e aritmética original preservadas.
- Também disponíveis os helpers originais de tipo, seleção SRC, FIR, depop e escrita de updates de 5 ms.
- AXSetMode/AXGetMode preservam o estado real de modo e o histórico HRTF usado pelo controle original. Isso não executa os comandos DSP/HRTF.
- Registro e execução dos callbacks auxiliares com três buffers, canais L/R/S e rotação original. Há um consumidor real `__AXProcessAux`; não são registros vazios.
- `DCFlushRangeNoSync` em `src/os_cache.c` emite `dcbf` nas linhas Xenon de 128 bytes, sem o `sync` final. As outras funções de cache mantêm sua barreira.

A única adaptação de declaração é transformar `ATTRIBUTE_ALIGN(32)` em `__declspec(align(32))` na posição aceita pelo compilador Microsoft. Assertions de compilação exigem AXPB=0xC0 e AXVPB=0x1F8, protegendo os offsets e tamanhos do inicializador original. Proveniência em `logs/portable-ax-provenance.json`.

## Validação no Xenia

`src/ax_control_probe.c` usa o código compilado para Xbox 360 e as funções reais de locking/cache. Executa somente com `verification.flag`; não adiciona esse custo ao boot normal.

Testa esgotamento das 64 vozes, identidade única, roubo FIFO por prioridade com callback, mudança de prioridade, liberação/reutilização, estado/depop, volumes assinados, ITD, endereços de 32 bits, formatos ADPCM/PCM16/PCM8, ganho correto em big-endian, cópias de estruturas, 21 valores de razão SRC até o clamp 4, 90 combinações de mix em cinco modos, rotação de três buffers auxiliares, canais, contexto dos callbacks, supressão de AuxB no modo 4 e desregistro.

Training e o preview Battlefield com AA são verificações de regressão do port existente, não partidas com Fighters originais. Os eventos de cenário ainda incluem quatro callbacks sem suporte. `verify-xenia.ps1` exige também o resultado AX=1.

## Limites e bloqueios reais

**O mixer DSP de vozes ainda não foi integrado ao XAudio2.** As vozes e os buffers CPU são funcionais e testados isoladamente; o caminho atual de HPS/efeitos continua separado. `AXInit` e `AXRegisterCallback` permanecem ausentes: a inicialização depende do SPB, command lists, serviço/sincronização de VPBs e saída DSP/AI, que não foram substituídos por handlers vazios. O teste chama os inicializadores CPU internos e limpa as listas/callbacks depois.

Dois comportamentos curiosos foram preservados do código original de Aux: o getter de entrada B consulta callback A e a inicialização limpa 480 longs por buffer de três blocos. A futura integração DSP deve revisar esses comportamentos e o reset dos demais blocos; não afirmar reset completo de todas as amostras.

Restam 44 nomes: 15 GX (iluminação/normais, texgen, cópia EFB e estados), 12 MCC, 6 THP, 4 AI, 3 OS, 2 AX e 2 símbolos de stack. Eles exigem caminhos de plataforma ou processamento reais. Essa contagem mede a auditoria de link desse caminho e não a porcentagem de conclusão do jogo.

Logs: `logs/ax-control-build.txt`, `logs/ax-control-training-passed.log`, `logs/ax-control-aa-stage-passed.log`, `logs/ax-control-fighter-audit.txt` e `logs/ax-control-hsd-audit.txt`.

## Build publicada

SHA-256: 4145665003B51B7FF29AD79CE8F732EC69ACDB0239EB3E057D50E941AD59ECE7

Caminho: package/RGH/Melee360/default.xex. Backup anterior: work/default-before-ax-control.xex. Perfil AA continua opcional; nenhum verification.flag foi copiado ao pacote normal. Validação feita no Xenia, não no console real nesta revisão.
