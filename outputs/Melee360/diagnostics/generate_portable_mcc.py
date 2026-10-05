from pathlib import Path
import re,json,hashlib
p=Path('outputs/Melee360'); source=Path('work/melee-base/libs/dolphin/src/dolphin/mcc/mcc.c');s=source.read_text()
s=s.replace('#include <dolphin.h>', '#include <dolphin/types.h>\n#include <dolphin/os.h>\n#include <dolphin/hio.h>\n#include <string.h>\nvoid Melee360HIOPump(void);')
s=re.sub(r'static ([^;\n]+) ATTRIBUTE_ALIGN\(32\);',r'static __declspec(align(32)) \1;',s)
s=s.replace('if (map[iMap] || iMap == 16)', 'if (iMap == 16 || map[iMap])')
s=s.replace('    volatile int result;\n    u8 count;', '    volatile int result;\n    u8 count = 0;')
s=s.replace('while (*flag != value) {', 'while (*flag != value) {\n        Melee360HIOPump();')
s=s.replace('    stat = AsyncResourceGetStat();', '    Melee360HIOPump();\n    stat = AsyncResourceGetStat();')
# The original assumes an interrupt callback. Native transport dispatches its actual incoming queue cooperatively.
# Never permit a negative transfer or unsigned range wrap through the original offset checks.
s=s.replace('if ((offset & 3) || ((u32) data & 0x1F) || (size % 32) != 0)', 'if (size < 0 || !data || (offset & 3) || ((u32) data & 0x1F) || (size % 32) != 0)')
s=s.replace('(offset + size) > gChannelInfo[chID].info.blockLength << 0xD', '(u32)size > (gChannelInfo[chID].info.blockLength << 0xD) - offset')
s=s.replace('offset + size > (gChannelInfo[chID].info.blockLength << 0xD)', '(u32)size > (gChannelInfo[chID].info.blockLength << 0xD) - offset')
(p/'compat/generated/portable_mcc.c').write_text(s)
(p/'logs/portable-mcc-provenance.json').write_text(json.dumps({'source':str(source),'sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'adaptations':['XDK alignment','native HIO header/includes','cooperative dispatch of actual incoming messages and completion events','fix original one-past-end map read','initialize original flush retry counter','reject negative/null transfer and overflowing ranges']},indent=2))
