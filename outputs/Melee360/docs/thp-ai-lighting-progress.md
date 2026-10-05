# THP, AI e iluminação GX — 2026-10-03

## Resultado

Auditorias de criação original Mario/Link, simples e com heap HSD: **41 → 29 símbolos ausentes**, zero duplicatas. O caminho Fighter ainda não linka nem foi executado. Nenhum stub ou /FORCE foi introduzido; a base em work/melee-base foi preservada.

Resolvidos neste lote:
- THPInit, THPVideoDecode, THPDec_8032F8D4, THPDec_8032FD40.
- AISetStreamVolLeft, AISetStreamVolRight (também getters).
- GXLoadLightObjImm, GXNormal3f32, GXSetChanAmbColor, GXSetChanCtrl, GXSetChanMatColor, GXSetNumChans.

## Escopo real

THP: código C original para descritor, tamanho do workspace, cabeçalhos, tabelas Huffman/quantização e preparação do decode. THPInit ganhou workspace alinhado nativo em lugar do locked cache Gekko. **Não decodifica pixels pelo decoder THP original**: IDCT/saída ainda dependem das duas funções ausentes. A intro continua com o decoder portátil existente. A API original não recebe tamanho de entrada; não é um parser seguro de arquivos arbitrários.

AI: ganhos esquerdo/direito aplicados à matriz real XAudio2 do stream HPS, preservando seleção Mono/Stereo. Aplicação no próximo AudioPump. Não substitui o relógio DSP ou inicialização AI original.

GX: estado de oito luzes, dois canais, fontes de material/ambiente, diffuse NONE/SIGN/CLAMP, atenuação spot/specular e multiplicação inteira de material. A iluminação é calculada por vértice na CPU e consumida pelo caminho nativo existente. Normais diretas e indexadas INDEX8/INDEX16 XYZ F32, matriz normal e display lists; **S8/S16/NBT/NBT3 não suportados**. Sete casos de aritmética CPU verificam luz 7, diffuse, atenuação e cores/canais. Não há ainda readback GPU específico de iluminação, nem certificação de equivalência completa com GX. Referência matemática: https://raw.githubusercontent.com/dolphin-emu/dolphin/master/Source/Core/VideoCommon/LightingShaderGen.cpp ; implementação própria, layout e contratos consultados no SDK original local.

## Bloqueios restantes (29)

- 6 GX: GXInvalidateVtxCache, GXSetDither, GXSetDstAlpha, GXSetNumTexGens, GXSetTexCoordGen2, GXSetZCompLoc. Exigem ligação correta ao fetch/cache, quantização, alpha de destino, geração de coordenadas/matrizes e ordem de depth/alpha.
- 12 MCC: MCCClose, MCCEnumDevices, MCCExit, MCCGetConnectionStatus, MCCGetFreeBlocks, MCCGetLastError, MCCInit, MCCNotify, MCCOpen, MCCRead, MCCStreamOpen, MCCWrite. MCC é comunicação host/HIO com mailbox e memória de adaptador; não é o memory card. Falta transporte e protocolo reais no Xbox.
- 2 THP: THPDec_80331340 e THPDec_803313D0, rotinas Gekko de decode/IDCT e saída para locked cache.
- 2 AI: AIInit e AISetDSPSampleRate; interrupções/clock 32/48 kHz do DSP ainda não traduzidos.
- 2 AX: AXInit e AXRegisterCallback; falta consumidor real por frame da command list/VPBs e mixer DSP. Apenas guardar callback sem executá-lo não resolve o contrato.
- 3 OS: OSCheckActiveThreads, OSGetResetCode, OSResetSystem; faltam integração com scheduler, razão real de reset e sequência de callbacks/reinício.
- 2 stack: _stack_addr e _stack_end; precisam dos limites reais de stack do runtime, não arrays fictícios.

## Evidências

Build XDK: logs/thp-ai-lighting-build.txt.
Auditorias: logs/fighter-create-mario-link-summary.json e logs/fighter-create-mario-link-hsd-main-heap-summary.json, ambas 29/0, linked=false/executed=false.
THP usa primeiro frame real de MvOpen.mth, sentinelas e workspace; AI usa quatro pares de limites e leitura da matriz XAudio2 real.
Regressão Training: logs/thp-ai-lighting-training-test.txt / thp-ai-lighting-training-passed.log.
Regressão áudio: logs/thp-ai-lighting-sound-test.txt.
A contagem mede linkagem deste caminho específico; não é porcentagem do jogo implementado. Testes deste lote usam Xenia, não console real.

Inventário público GX separado: 110 símbolos compilados, 2 inline e 138 ausentes em 250 APIs. Os 6 GX restantes acima são apenas os exigidos pelo caminho Fighter auditado.

Build publicada: package/RGH/Melee360/default.xex. SHA256 B10DFF7870442470EBA4810BB6E526844BB9EE9EDF86597EAE01D4D3E92DE6CA. Backup: work/default-before-thp-ai-lighting.xex.
Training, SoundPreview e StagePreview com AA passaram no Xenia. Battlefield: quatro variantes, 120 atualizações cada; callbacks não suportados 4/4/4/2. Teste de cenário é prévia animada, não gameplay. Log AA: logs/thp-ai-lighting-aa-stage-passed.log. O pacote publicado não contém hsd-aa.flag.
