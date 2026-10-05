import hashlib, json
from pathlib import Path
project = Path(__file__).resolve().parents[1]
base = project.parents[1] / 'work/melee-base'
source = base / 'libs/dolphin/src/dolphin/os/OSAlloc.c'
original = source.read_text()
body = original.replace('#include <dolphin.h>', '''/* Original allocator, debug bookkeeping enabled on both platforms. */
#include <dolphin/types.h>
#include <dolphin/os.h>
#include <stddef.h>
#define DEBUG 1
#undef ASSERTMSGLINE
#undef ASSERTLINE
#define ASSERTMSGLINE(line, condition, message) do { if (!(condition)) __assert(__FILE__, line, message); } while (0)
#define ASSERTLINE(line, condition) ASSERTMSGLINE(line, condition, #condition)
#ifndef OFFSET
#define OFFSET(value, alignment) ((u32)(value) & ((alignment)-1))
#endif''')
# MSVC rejects arithmetic on void pointers; this only occurs in a debug check.
body = body.replace('ArenaStart + HEADERSIZE', '(u8*) ArenaStart + HEADERSIZE')
body += '\n/* -1 invalid/destroyed, 0 empty, 1 allocated; includes direct OS allocations. */\nint Melee360OSHeapAllocationState(int heap) { if (!HeapArray || heap < 0 || heap >= NumHeaps || HeapArray[heap].size < 0) return -1; return HeapArray[heap].allocated != NULL; }\n'
body += '\n#if !defined(_WIN64)\ntypedef char heap_cell_size_check[sizeof(struct Cell)==20?1:-1];\ntypedef char heap_desc_size_check[sizeof(struct HeapDesc)==24?1:-1];\n#else\n#error Original allocator requires a 32-bit target\n#endif\n'
(project / 'compat/generated/os_allocator.c').write_text(body)
(project / 'logs/os-allocator-provenance.json').write_text(json.dumps({
    'source': str(source), 'sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
    'adaptations': ['replace umbrella includes and assertion macros', 'enable original debug bookkeeping', 'cast void pointer to byte pointer for debug range check', 'expose read-only allocation state for HSD lifetime checks'],
    'implementation': 'Original OSAlloc.c algorithm and functions; no malloc replacement'
}, indent=2))
print('Generated original 32-bit OS allocator')

