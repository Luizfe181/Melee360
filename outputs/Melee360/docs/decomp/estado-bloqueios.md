# Estado real do port

Snapshot atual da auditoria Mario/Link: 109 símbolos ausentes, zero duplicatas, linked=false, executed=false. Não indica que todos são chamados no primeiro frame: link retém módulos, dados e tabelas de callbacks. Resolvê-los não garante init, assets ou execução corretos.

| Situação | Evidência / limite |
|---|---|
| 986/987 entradas compiladas | inventário histórico de compilação; não significa runtime integrado |
| Boot, intro, menus, CSS/SSS previews | testes Xenia e relatos históricos de hardware; previews não são cena/gameplay original completa |
| Dados Mario/Link/Battlefield | loader/probes de atributos e geometria; sem Fighter criado |
| Lógica original isolada | 19 rotinas e testes; não scheduler completo nem ECB |
| Efeitos e HPS | processamento e streaming verificáveis; sem AX voice engine |
| Auditoria Mario/Link | ainda não liga; entry não está na XEX |

## Ausências por grupo

| Grupo | Quantidade |
|---|---:|
| OS/stack | 5 |
| AI/AX | 26 |
| GX | 50 |
| HSD | 4 |
| MCC | 12 |
| THP | 6 |
| VI | 6 |

### OS/stack

`_stack_addr`, `_stack_end`, `OSCheckActiveThreads`, `OSGetResetCode`, `OSResetSystem`

### AI/AX

`AIInit`, `AISetDSPSampleRate`, `AISetStreamVolLeft`, `AISetStreamVolRight`, `AXAcquireVoice`, `AXFreeVoice`, `AXInit`, `AXRegisterAuxACallback`, `AXRegisterAuxBCallback`, `AXRegisterCallback`, `AXSetVoiceAddr`, `AXSetVoiceAdpcm`, `AXSetVoiceAdpcmLoop`, `AXSetVoiceCurrentAddr`, `AXSetVoiceEndAddr`, `AXSetVoiceItdOn`, `AXSetVoiceItdTarget`, `AXSetVoiceLoop`, `AXSetVoiceLoopAddr`, `AXSetVoiceMix`, `AXSetVoicePriority`, `AXSetVoiceSrc`, `AXSetVoiceSrcRatio`, `AXSetVoiceState`, `AXSetVoiceVe`, `AXSetVoiceVeDelta`

### GX

`GXCopyDisp`, `GXCopyTex`, `GXEnableTexOffsets`, `GXInvalidateTexAll`, `GXInvalidateVtxCache`, `GXLoadLightObjImm`, `GXNormal3f32`, `GXSetChanAmbColor`, `GXSetChanCtrl`, `GXSetChanMatColor`, `GXSetCopyClamp`, `GXSetCopyClear`, `GXSetCopyFilter`, `GXSetDispCopyDst`, `GXSetDispCopyGamma`, `GXSetDispCopySrc`, `GXSetDispCopyYScale`, `GXSetDither`, `GXSetDstAlpha`, `GXSetFog`, `GXSetFogRangeAdj`, `GXSetIndTexCoordScale`, `GXSetIndTexMtx`, `GXSetIndTexOrder`, `GXSetLineWidth`, `GXSetNumChans`, `GXSetNumIndStages`, `GXSetNumTevStages`, `GXSetNumTexGens`, `GXSetPointSize`, `GXSetTevAlphaIn`, `GXSetTevAlphaOp`, `GXSetTevClampMode`, `GXSetTevColor`, `GXSetTevColorIn`, `GXSetTevColorOp`, `GXSetTevColorS10`, `GXSetTevDirect`, `GXSetTevIndirect`, `GXSetTevKAlphaSel`, `GXSetTevKColor`, `GXSetTevKColorSel`, `GXSetTevOp`, `GXSetTevSwapMode`, `GXSetTevSwapModeTable`, `GXSetTexCoordGen2`, `GXSetTexCopyDst`, `GXSetTexCopySrc`, `GXSetZCompLoc`, `GXSetZTexture`

### HSD

`HSD_CreateMainHeap`, `HSD_GetCurrentRenderPass`, `HSD_Init_803755A8`, `HSD_StartRender`

### MCC

`MCCClose`, `MCCEnumDevices`, `MCCExit`, `MCCGetConnectionStatus`, `MCCGetFreeBlocks`, `MCCGetLastError`, `MCCInit`, `MCCNotify`, `MCCOpen`, `MCCRead`, `MCCStreamOpen`, `MCCWrite`

### THP

`THPDec_8032F8D4`, `THPDec_8032FD40`, `THPDec_80331340`, `THPDec_803313D0`, `THPInit`, `THPVideoDecode`

### VI

`VIConfigure`, `VIFlush`, `VIGetNextField`, `VISetBlack`, `VISetNextFrameBuffer`, `VIWaitForRetrace`

## Limites de conhecimento

O inventário enumera todo o código encontrado, mas o exame semântico concentrou-se em gmmain/main, Fighter_Create/scheduler, initialize/HSD, headers/plataforma e artefatos do port. Funções de estados individuais, todos os itens/stages, menus completos e modos secundários ainda precisam de análise por caminho. Não tratamos um índice gerado como prova de domínio de cada rotina.

Risco imediato: original initialize.c e adaptador hsd_memory podem disputar ownership; consulta de RAM física não corrige aritmética de endereços GameCube. Render ausente não elimina joints necessários a ECB. Bancos de áudio não são HPS. Em runtime poderão aparecer bloqueios além dos símbolos do link.

## Auditoria ampliada de inicializacao HSD

O caminho de auditoria com os corpos originais de heap e StartRender tem 111 ausencias (tres HSD resolvidas, duas GX novas), sem integrar essas rotinas ao runtime. Veja [resultado detalhado](../hsd-original-initialization-audit.md). O snapshot normal acima continua em 112.

GXSetPixelFmt agora tem suporte parcial RGB8/Z24 e depth-only no runtime, com probe. A auditoria HSD ampliada caiu para 110, enquanto a normal conserva 112. GXSetFieldMode permanece ausente. Veja [validacao](../gx-pixel-format-progress.md).

Ligacao inicial de GXLoadTexObj implementada para TEXMAP0 sem paleta/mipmaps. Auditoria ampliada HSD atual: 109. Veja [resultado](../gx-texture-binding-progress.md).

Atualizacao de texturas: mipmaps, paletas e oito slots agora disponiveis no caminho direto; normal 109/ampliada HSD 107. APIs TEV ainda parciais; [contratos](../gx-mipmaps-palettes-units-progress.md).
