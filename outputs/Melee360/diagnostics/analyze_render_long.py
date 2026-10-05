from pathlib import Path
import json,re
root=Path(__file__).resolve().parents[1];folder=root/'logs/render-isolation-current'
runs={}
for name in ('long-visible','long-hidden'):
    text=(folder/(name+'.txt')).read_text(encoding='utf-8-sig')
    assert 'Original match render: 900 frames presented' in text and 'FAILED' not in text and 'DMA stopped' not in text,name
    def rows(prefix):
        return [{k:float(v) for k,v in re.findall(r'(\w+)=([\d.]+)',line)} for line in text.splitlines() if line.startswith(prefix)]
    profile=rows('GX profile: frames=');detail=rows('GX detail: frames=');first=next(x for x in profile if x['frames']==180);last=next(x for x in profile if x['frames']==900)
    steady={k:(last[k]*900-first[k]*180)/720 for k in last if k.endswith('_ms')}
    steady.update({k:(last[k]-first[k])/720 for k in ('uploads','copies','cache_hits','draws','constant_writes')})
    assert last['frames']==900
    runs[name]={'profile':profile,'detail':detail,'steadyFrames181to900':steady,'cpu':re.findall(r'^Original CPU: .*$',text,re.M)}
report={'runs':runs,'cpuSamplesIdentical':runs['long-visible']['cpu']==runs['long-hidden']['cpu'],'scope':'Same original simulation, 900 frames per run; CPU wall time. Steady figures subtract cumulative first 180 frames. No physical console measurement.'}
assert report['cpuSamplesIdentical'],'Long CPU sampled states diverged; investigate before claiming equivalence'
(folder/'long-analysis.json').write_text(json.dumps(report,indent=2))
print('Long CPU states identical:',report['cpuSamplesIdentical'])
for name,run in runs.items():print(name,json.dumps(run['steadyFrames181to900']))
with (root/'docs/render-isolation-current.md').open('a',encoding='utf-8') as f:
    f.write('\n## Combate prolongado\n\nDuas execucoes adicionais de 900 frames. Os estados CPU amostrados coincidiram, e o audio continuou ativo. Valores abaixo calculados somente para frames 181 a 900, retirando a media acumulada dos primeiros 180.\n\n| Medida | Visiveis | Ocultos |\n|---|---:|---:|\n')
    for key in ('logic_ms','render_ms','upload_ms','copy_ms','pipeline_ms','uploads','draws'):
        f.write(f"| {key} por frame | {runs['long-visible']['steadyFrames181to900'][key]:.3f} | {runs['long-hidden']['steadyFrames181to900'][key]:.3f} |\n")
    f.write('\nDados e evolucao por blocos de 60 frames: logs/render-isolation-current/long-analysis.json.\n')
