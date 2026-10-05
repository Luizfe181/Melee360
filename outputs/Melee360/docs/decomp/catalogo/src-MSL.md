# Catálogo: src/MSL

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/MSL/abort_exit.c`

48 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/os/init/__ppc_eabi_init.h`

Definições aparentes: `exit`

## `src/MSL/abort_exit.h`

6 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/ansi_files.c`

101 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `console_io.h`, `stdio.h`

## `src/MSL/ansi_fp.c`

163 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `ansi_fp.h`, `math.h`

Definições aparentes: `_fpclassify`, `__num2dec`

## `src/MSL/ansi_fp.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/buffer_io.c`

35 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `buffer_io.h`

Definições aparentes: `__prep_buffer`, `__flush_buffer`

## `src/MSL/buffer_io.h`

17 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `stdio.h`

## `src/MSL/console_io.h`

13 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `stdio.h`

## `src/MSL/ctype.c`

93 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `ctype.h`

Definições aparentes: `tolower`, `toupper`

## `src/MSL/ctype.h`

50 linhas; 5 definições aparentes; 0 marcadores asm.

Definições aparentes: `isalpha`, `isdigit`, `isspace`, `isupper`, `isxdigit`

## `src/MSL/direct_io.c`

116 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `buffer_io.h`, `stdio.h`, `string.h`, `wchar.h`

Definições aparentes: `fwrite`

## `src/MSL/errno.c`

3 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `errno.h`

## `src/MSL/errno.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/float.c`

2 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/limits.h`

141 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/math.c`

113 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `math.h`

Definições aparentes: `logf`

## `src/MSL/math.h`

97 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `math_ppc.h`, `MetroTRK/intrinsics.h`

Definições aparentes: `__fpclassifyf`, `__fpclassifyd`, `fabs`, `fmodf`

## `src/MSL/math_1.c`

33 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `math.h`

Definições aparentes: `tanf`, `fabsf__Ff`, `frexp`

## `src/MSL/math_data.c`

76 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/math_ppc.h`

50 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `MetroTRK/intrinsics.h`

Definições aparentes: `sqrtf`, `sqrtf_accurate`

## `src/MSL/mbstring.c`

18 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `stdlib.h`

Definições aparentes: `wcstombs`

## `src/MSL/mem.c`

84 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `mem_funcs.h`, `string.h`

Definições aparentes: `memmove`, `memchr`, `memcmp`

## `src/MSL/mem_funcs.c`

239 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `mem_funcs.h`

Definições aparentes: `__copy_longs_aligned`, `__copy_longs_rev_aligned`, `__copy_longs_unaligned`, `__copy_longs_rev_unaligned`

## `src/MSL/mem_funcs.h`

13 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `stddef.h`

## `src/MSL/misc_io.c`

3 linhas; 1 definições aparentes; 0 marcadores asm.

Definições aparentes: `__stdio_atexit`

## `src/MSL/PPC_EABI/critical_regions.gamecube.c`

6 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `critical_regions.gamecube.h`

Definições aparentes: `__kill_critical_regions`

## `src/MSL/PPC_EABI/critical_regions.gamecube.h`

6 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/printf.c`

1090 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `printf.h`, `ansi_fp.h`, `ctype.h`, `limits.h`, `stdarg.h`, `stdio.h`, `stdlib.h`, `string.h`, `wchar.h`, `dolphin/types.h`

Definições aparentes: `parse_format`, `long2str`, `longlong2str`, `round_decimal`, `float2str`, `__pformatter`, `__FileWrite`, `__StringWrite`, `printf`, `vprintf`, `vsnprintf`, `vsprintf`, `sprintf`

## `src/MSL/printf.h`

4 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/rand.c`

15 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `stdlib.h`, `dolphin/types.h`

Definições aparentes: `rand`, `srand`

## `src/MSL/setjmp.h`

6 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/Gecko_setjmp.h`

## `src/MSL/stdarg.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/stdbool.h`

16 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/stddef.h`

22 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/stdio.h`

136 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `stdarg.h`, `stddef.h`

## `src/MSL/stdlib.h`

29 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `stddef.h`, `strtoul.h`, `wchar.h`

Definições aparentes: `abs`

## `src/MSL/string.c`

322 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `string.h`, `stdio.h`

Definições aparentes: `strcpy`, `strncpy`, `strcmp`, `strncmp`, `strchr`, `__StringRead`

## `src/MSL/string.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `stddef.h`

## `src/MSL/strtoul.c`

214 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `strtoul.h`, `ctype.h`, `errno.h`, `limits.h`, `stdio.h`, `stdlib.h`, `dolphin/types.h`

Definições aparentes: `__strtoul`, `strtoul`, `strtol`, `atoi`

## `src/MSL/strtoul.h`

18 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/sys/types.h`

7 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/MSL/trigf.c`

117 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `math.h`

Definições aparentes: `__sinit_trigf_c`, `sinf`, `cosf`, `sin__Ff`, `cos__Ff`

## `src/MSL/uart_console_io.c`

71 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `console_io.h`

Definições aparentes: `__read_console`, `__write_console`, `__close_console`

## `src/MSL/wchar.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `stdio.h`

## `src/MSL/wchar_io.c`

29 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `stdio.h`, `wchar.h`

Definições aparentes: `fwide`

