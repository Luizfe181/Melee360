# Catálogo: src/Runtime

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/Runtime/__init_cpp_exceptions.c`

39 linhas; 3 definições aparentes; 1 marcadores asm.

Includes: `__init_cpp_exceptions.h`, `Gecko_ExceptionPPC.h`, `platform.h`

Definições aparentes: `GetR2`, `__fini_cpp_exceptions`, `__init_cpp_exceptions`

## `src/Runtime/__init_cpp_exceptions.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/Runtime/__mem.c`

91 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `string.h`, `platform.h`

Definições aparentes: `memset`, `__fill_mem`, `memcpy`

## `src/Runtime/__va_arg.c`

59 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `stdarg.h`, `platform.h`

Definições aparentes: `__va_arg`

## `src/Runtime/eabi_save_restore.s`

107 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/Runtime/Gecko_ExceptionPPC.c`

41 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `Gecko_ExceptionPPC.h`

Definições aparentes: `__unregister_fragment`, `__register_fragment`

## `src/Runtime/Gecko_ExceptionPPC.h`

14 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/Runtime/Gecko_setjmp.c`

77 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `Gecko_setjmp.h`, `platform.h`

Definições aparentes: `__setjmp`, `__longjmp`

## `src/Runtime/Gecko_setjmp.h`

37 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/Runtime/global_destructor_chain.c`

23 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `global_destructor_chain.h`, `platform.h`

Definições aparentes: `__destroy_global_chain`

## `src/Runtime/global_destructor_chain.h`

6 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/Runtime/platform.h`

182 linhas; 0 definições aparentes; 1 marcadores asm.

Includes: `stdbool.h`, `stddef.h`, `dolphin/types.h`, `sys/types.h`

## `src/Runtime/runtime.c`

584 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `runtime.h`

Definições aparentes: `__cvt_fp2unsigned`, `__div2u`, `__div2i`, `__mod2u`, `__mod2i`, `__shl2i`, `__shr2u`, `__shr2i`, `__cvt_sll_dbl`, `__cvt_sll_flt`, `__cvt_dbl_usll`

## `src/Runtime/runtime.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

