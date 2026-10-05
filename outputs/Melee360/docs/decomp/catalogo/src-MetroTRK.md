# Catálogo: src/MetroTRK

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/MetroTRK/__exception.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/MetroTRK/__exception.s`

156 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MetroTRK/dispatch.c`

65 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `dispatch.h`, `msghndlr.h`

Definições aparentes: `TRKInitializeDispatcher`, `TRKDispatchMessage`

## `src/MetroTRK/dispatch.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `MetroTRK/dserror.h`, `MetroTRK/msgbuf.h`

## `src/MetroTRK/dolphin_trk.c`

161 linhas; 7 definições aparentes; 0 marcadores asm.

Includes: `dolphin_trk.h`, `__exception.h`, `dolphin_trk_glue.h`, `flush_cache.h`, `mem_TRK.h`, `ppc_except.h`, `ppc_targimpl.h`, `mpc_7xx_603e.h`

Definições aparentes: `__TRK_reset`, `InitMetroTRK`, `EnableMetroTRKInterrupts`, `TRKTargetTranslate`, `TRK_copy_vector`, `__TRK_copy_vectors`, `TRKInitializeTarget`

## `src/MetroTRK/dolphin_trk.h`

14 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/dserror.h`

## `src/MetroTRK/dolphin_trk_glue.c`

136 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `dolphin_trk_glue.h`, `mem_TRK.h`, `targimpl.h`, `trk.h`, `dolphin/amc/AmcExi2Comm.h`, `dolphin/db/DBInterface.h`, `dolphin/odemu/odemu.h`, `dolphin/os/OSThread.h`

Definições aparentes: `TRKLoadContext`, `TRKEXICallBack`, `InitMetroTRKCommTable`, `TRKUARTInterruptHandler`, `TRKInitializeIntDrivenUART`, `EnableEXI2Interrupts`, `TRKPollUART`, `TRK_ReadUARTN`, `TRK_WriteUARTN`, `ReserveEXI2Port`, `UnreserveEXI2Port`, `TRK_board_display`

## `src/MetroTRK/dolphin_trk_glue.h`

43 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/os.h`, `MetroTRK/dserror.h`

## `src/MetroTRK/dserror.h`

24 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MetroTRK/flush_cache.c`

25 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `flush_cache.h`

Definições aparentes: `TRK_flush_cache`

## `src/MetroTRK/flush_cache.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/MetroTRK/intrinsics.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `stddef.h`

## `src/MetroTRK/m7xx_m603e_reg.h`

104 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/ppc_reg.h`

## `src/MetroTRK/main_TRK.c`

23 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `main_TRK.h`, `mainloop.h`, `nubinit.h`

Definições aparentes: `TRKTargetCPUMinorType`, `TRK_main`

## `src/MetroTRK/main_TRK.h`

9 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/MetroTRK/mainloop.c`

61 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `mainloop.h`, `dispatch.h`, `msgbuf.h`, `serpoll.h`, `targcont.h`, `targimpl.h`

Definições aparentes: `TRKHandleRequestEvent`, `TRKHandleSupportEvent`, `TRKIdle`, `TRKNubMainLoop`

## `src/MetroTRK/mainloop.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `MetroTRK/nubevent.h`

## `src/MetroTRK/mem_TRK.c`

82 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `mem_TRK.h`

Definições aparentes: `TRK_memcpy`, `TRK_memset`, `TRK_fill_mem`

## `src/MetroTRK/mem_TRK.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/MetroTRK/memmap.h`

16 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/MetroTRK/mpc_7xx_603e.c`

285 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `mpc_7xx_603e.h`, `ppc_targimpl.h`

Definições aparentes: `TRKSaveExtended1Block`, `TRKRestoreExtended1Block`

## `src/MetroTRK/mpc_7xx_603e.h`

9 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/MetroTRK/msg.c`

8 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `msg.h`, `dolphin_trk_glue.h`

Definições aparentes: `TRKMessageSend`

## `src/MetroTRK/msg.h`

16 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/dserror.h`, `MetroTRK/msgbuf.h`

## `src/MetroTRK/msgbuf.c`

368 linhas; 20 definições aparentes; 0 marcadores asm.

Includes: `msgbuf.h`, `mem_TRK.h`, `nubinit.h`

Definições aparentes: `TRKSetBufferUsed`, `TRKInitializeMessageBuffers`, `TRKGetFreeBuffer`, `TRKGetBuffer`, `TRKReleaseBuffer`, `TRKResetBuffer`, `TRKSetBufferPosition`, `TRKAppendBuffer`, `TRKReadBuffer`, `TRKAppendBuffer1_ui16`, `TRKAppendBuffer1_ui32`, `TRKAppendBuffer1_ui64`, `TRKAppendBuffer_ui8`, `TRKAppendBuffer_ui32`, `TRKReadBuffer1_ui8`, `TRKReadBuffer1_ui16`, `TRKReadBuffer1_ui32`, `TRKReadBuffer1_ui64`, `TRKReadBuffer_ui8`, `TRKReadBuffer_ui32`

## `src/MetroTRK/msgbuf.h`

73 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/dserror.h`, `MetroTRK/mutex_TRK.h`

Definições aparentes: `TRKAppendBuffer1_ui8`

## `src/MetroTRK/msgcmd.h`

294 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/MetroTRK/msghndlr.c`

725 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `msghndlr.h`, `msg.h`, `msgbuf.h`, `nubevent.h`, `targcont.h`, `targimpl.h`

Definições aparentes: `TRKMessageIntoReply`, `TRKSendACK`, `TRKStandardACK`, `TRKDoUnsupported`, `TRKDoConnect`, `TRKDoDisconnect`, `TRKDoReset`, `TRKDoOverride`, `TRKDoVersions`, `TRKDoSupportMask`, `TRKDoCPUType`, `TRKDoReadMemory`, `TRKDoWriteMemory`, `TRKDoReadRegisters`, `TRKDoWriteRegisters`, `TRKDoFlushCache`, `TRKDoContinue`, `TRKDoStep`, `TRKDoStop`

## `src/MetroTRK/msghndlr.h`

47 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/dserror.h`, `MetroTRK/msgbuf.h`, `MetroTRK/msgcmd.h`

## `src/MetroTRK/mutex_TRK.c`

18 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `mutex_TRK.h`, `dserror.h`

Definições aparentes: `TRKInitializeMutex`, `TRKAcquireMutex`, `TRKReleaseMutex`

## `src/MetroTRK/mutex_TRK.h`

12 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `MetroTRK/dserror.h`

## `src/MetroTRK/notify.c`

37 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `notify.h`, `msgbuf.h`, `support.h`, `targimpl.h`

Definições aparentes: `TRKDoNotifyStopped`

## `src/MetroTRK/notify.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/dserror.h`

## `src/MetroTRK/nubevent.c`

89 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `nubevent.h`, `mem_TRK.h`

Definições aparentes: `TRKInitializeEventQueue`, `TRKCopyEvent`, `TRKGetNextEvent`, `TRKPostEvent`, `TRKConstructEvent`, `TRKDestructEvent`

## `src/MetroTRK/nubevent.h`

33 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/dserror.h`, `MetroTRK/msgbuf.h`

## `src/MetroTRK/nubinit.c`

90 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `nubinit.h`, `dispatch.h`, `dolphin_trk.h`, `dolphin_trk_glue.h`, `msgbuf.h`, `serpoll.h`, `targimpl.h`, `usr_put.h`

Definições aparentes: `TRKInitializeNub`, `TRKTerminateNub`, `TRKNubWelcome`, `TRKInitializeEndian`

## `src/MetroTRK/nubinit.h`

15 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/dserror.h`

## `src/MetroTRK/ppc_except.h`

50 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MetroTRK/ppc_mem.h`

21 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

Definições aparentes: `ppc_readbyte1`, `ppc_writebyte1`

## `src/MetroTRK/ppc_reg.h`

229 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/MetroTRK/ppc_targimpl.h`

62 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/dserror.h`, `MetroTRK/m7xx_m603e_reg.h`, `MetroTRK/ppc_reg.h`

## `src/MetroTRK/serpoll.c`

85 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `serpoll.h`, `dolphin_trk_glue.h`, `msgbuf.h`, `msghndlr.h`, `nubevent.h`

Definições aparentes: `TRKTestForPacket`, `TRKGetInput`, `TRKProcessInput`, `TRKInitializeSerialHandler`, `TRKTerminateSerialHandler`

## `src/MetroTRK/serpoll.h`

33 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/msgbuf.h`

## `src/MetroTRK/support.c`

196 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `support.h`, `msg.h`, `msgcmd.h`, `serpoll.h`

Definições aparentes: `TRKSuppAccessFile`, `TRKRequestSend`

## `src/MetroTRK/support.h`

16 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `MetroTRK/msgbuf.h`, `MetroTRK/msgcmd.h`

## `src/MetroTRK/targcont.c`

13 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `targcont.h`, `dolphin_trk_glue.h`, `targimpl.h`

Definições aparentes: `TRKTargetContinue`

## `src/MetroTRK/targcont.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `MetroTRK/dserror.h`

## `src/MetroTRK/target_options.h`

9 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/MetroTRK/targimpl.c`

1148 linhas; 39 definições aparentes; 0 marcadores asm.

Includes: `targimpl.h`, `dolphin_trk.h`, `dserror.h`, `flush_cache.h`, `m7xx_m603e_reg.h`, `main_TRK.h`, `memmap.h`, `msgbuf.h`, `msgcmd.h`, `notify.h`, `nubevent.h`, `nubinit.h`, `ppc_except.h`, `ppc_reg.h`, `ppc_targimpl.h`, `support.h`, `dolphin_trk_glue.h`, `mpc_7xx_603e.h`

Definições aparentes: `__TRK_get_MSR`, `__TRK_set_MSR`, `TRKValidMemory32`, `TRK_ppc_memcpy`, `TRKTargetAccessMemory`, `TRKTargetReadInstruction`, `TRKTargetAccessDefault`, `TRKTargetAccessFP`, `TRKTargetAccessExtended1`, `TRKTargetAccessExtended2`, `TRKTargetVersions`, `TRKTargetSupportMask`, `TRKTargetCPUType`, `TRKInterruptHandler`, `TRKExceptionHandler`, `TRKPostInterruptEvent`, `TRKSwapAndGo`, `TRKInterruptHandlerEnableInterrupts`, `TRKTargetInterrupt`, `TRKTargetAddStopInfo`, `TRKTargetAddExceptionInfo`, `TRKTargetEnableTrace`, `TRKTargetStepDone`, `TRKTargetDoStep`, `TRKTargetCheckStep`, `TRKTargetSingleStep`, `TRKTargetStepOutOfRange`, `TRKTargetGetPC`, `TRKTargetSupportRequest`, `TRKTargetFlushCache`, `TRKTargetStopped`, `TRKTargetSetStopped`, `TRKTargetStop`, `TRKPPCAccessSPR`, `TRKPPCAccessPairedSingleRegister`, `TRKPPCAccessFPRegister`, `TRKPPCAccessSpecialReg`, `TRKTargetSetInputPendingPtr`, `ConvertAddress`

## `src/MetroTRK/targimpl.h`

72 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/os/OSThread.h`, `MetroTRK/msgbuf.h`, `MetroTRK/msgcmd.h`, `MetroTRK/nubevent.h`

## `src/MetroTRK/targsupp.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/MetroTRK/trk.h`

4 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MetroTRK/usr_put.c`

5 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `usr_put.h`

Definições aparentes: `usr_put_initialize`

## `src/MetroTRK/usr_put.h`

7 linhas; 0 definições aparentes; 0 marcadores asm.

