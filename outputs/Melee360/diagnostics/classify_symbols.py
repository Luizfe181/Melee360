"""Locate candidate definitions, not just declarations, for link failures.
Lexical C scan: candidate availability must still be verified by compilation/link.
"""
import argparse, json, re
from pathlib import Path

p = argparse.ArgumentParser()
p.add_argument('--base', required=True)
p.add_argument('--project', required=True)
a = p.parse_args()
base, project = Path(a.base), Path(a.project)
logs = project / 'logs' / 'gameplay-compile'
baseline = logs / 'baseline-745-symbols.txt'
if not baseline.exists():
    baseline.write_text((logs / 'link-missing-symbols.txt').read_text(encoding='utf-8-sig'), encoding='utf-8')
names = set(baseline.read_text(encoding='utf-8-sig').split())
providers = {n: [] for n in names}
token = re.compile(r'\b([A-Za-z_]\w*)\b')
comments = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)

for root, kind in [(base/'src', 'upstream'), (base/'libs', 'upstream'), (project/'src', 'port')]:
    for file in sorted(root.rglob('*')):
        if file.suffix not in ('.c', '.cpp'): continue
        text = file.read_text(encoding='utf-8', errors='replace')
        clean = comments.sub(lambda m: ''.join('\n' if c=='\n' else ' ' for c in m[0]), text)
        depth, last = 0, 0
        levels = []
        for char in clean:
            levels.append(depth)
            if char == '{': depth += 1
            elif char == '}': depth -= 1
        for match in token.finditer(clean):
            name = match[1]
            if name not in names: continue
            end = match.end()
            while end < len(clean) and clean[end].isspace(): end += 1
            before = clean[max(clean.rfind(';',0,match.start()), clean.rfind('}',0,match.start()), clean.rfind('{',0,match.start()))+1:match.start()]
            if re.search(r'\bstatic\b', before): continue
            category = None
            if end < len(clean) and clean[end] == '(':
                level, pos = 1, end+1
                while pos < len(clean) and level:
                    if clean[pos]=='(': level+=1
                    elif clean[pos]==')': level-=1
                    pos+=1
                while pos<len(clean) and clean[pos].isspace():pos+=1
                if pos<len(clean) and clean[pos]=='{' and not re.search(r'\b(return|if|while|switch)\b|=', before):category='function'
            elif levels[match.start()]==0:
                pos=end
                if pos<len(clean) and clean[pos]=='[':
                    pos=clean.find(']',pos)+1
                    while pos<len(clean) and clean[pos].isspace():pos+=1
                if pos<len(clean) and clean[pos]=='=':category='data'
                elif pos<len(clean) and clean[pos] in ';,' and not re.search(r'\b(extern|typedef)\b|=',before):category='data'
            if category:
                origin = base if kind=='upstream' else project
                entry={'origin':kind,'path':str(file.relative_to(origin)).replace('\\','/'),'line':clean.count('\n',0,match.start())+1,'kind':category}
                if entry not in providers[name]:providers[name].append(entry)
        for match in re.finditer(r'\(\s*\*\s*(\w+)\s*\)\s*\([^;]*?\)\s*=',clean):
            name=match[1]
            if name in names and levels[match.start()]==0:
                origin=base if kind=='upstream' else project
                entry={'origin':kind,'path':str(file.relative_to(origin)).replace('\\','/'),'line':clean.count('\n',0,match.start())+1,'kind':'data'}
                if entry not in providers[name]:providers[name].append(entry)

for file,kind,root in [(base/'src/Runtime/platform.h','upstream',base),(project/'compat/Runtime/platform.h','port',project)]:
    for line_no,line in enumerate(file.read_text(encoding='utf-8').splitlines(),1):
        m=re.match(r'\s*#define\s+(\w+)',line)
        if m and m[1] in names:
            providers[m[1]].append({'origin':kind,'path':str(file.relative_to(root)).replace('\\','/'),'line':line_no,'kind':'macro'})

rows=[]
for name in sorted(names):
    hits=providers[name]
    if any(h['origin']=='port' for h in hits):group='existing-port-candidate'
    elif hits:group='upstream-source-candidate'
    elif re.match(r'^(GX|__GX|OS|__OS|DVD|CARD|AR|AI|AX|VI|PAD|Melee360OS)',name):group='platform-or-sdk-boundary'
    else:group='no-definition-found'
    rows.append({'symbol':name,'group':group,'candidates':hits})
(logs/'symbol-providers.json').write_text(json.dumps(rows,indent=2,ensure_ascii=False),encoding='utf-8')
summary={g:sum(r['group']==g for r in rows) for g in sorted({r['group'] for r in rows})}
(logs/'symbol-provider-summary.json').write_text(json.dumps(summary,indent=2),encoding='utf-8')
print(json.dumps(summary,indent=2))
print('Candidates are lexical matches; exports, ABI and runtime readiness require separate verification.')
