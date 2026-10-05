from pathlib import Path
import json,re
root=Path(__file__).resolve().parents[1]
folder=root/'logs/render-isolation-current'
manifest=json.loads((folder/'manifest.json').read_text(encoding='utf-8-sig'))
runs={}
for test in manifest['Tests']:
    name=test['Name'];text=(folder/(name+'.txt')).read_text(encoding='utf-8-sig')
    assert 'GX profile: 180 frames presented' in text,name
    assert 'FAILED' not in text and 'DMA stopped' not in text,name
    def row(prefix):
        line=next((x for x in text.splitlines() if x.startswith(prefix+' frames=180 ')),None)
        return {k:float(v) for k,v in re.findall(r'(\w+)=([\d.]+)',line)} if line else None
    profile=row('GX profile:');profile['frame_ms']=sum(profile[k] for k in ('logic_ms','render_ms','present_ms'))
    samples={}
    for line in text.splitlines():
        if line.startswith('GX vertex sample: frames=180 '):
            samples[re.search(r'kind=(\w+)',line)[1]]={k:float(v) for k,v in re.findall(r'(\w+)=([\d.]+)',line)}
    runs[name]={'profile':profile,'detail':row('GX detail:'),'samples':samples,'cpu':re.findall(r'^Original CPU: .*$',text,re.M)}
ref=runs['baseline-before']['profile'];after=runs['baseline-after']['profile']
for name,run in runs.items():
    run['cpuMatchesBaseline']=run['cpu']==runs['baseline-before']['cpu']
    run['renderReductionPercentRange']=sorted([100*(1-run['profile']['render_ms']/base['render_ms']) for base in (ref,after)])
    assert run['cpuMatchesBaseline'],name
    if name!='detail-hidden':assert run['profile']['draws']==ref['draws'],name
ranges={kind:[min(runs[n]['samples'][kind]['estimated_ms'] for n in ('vertex-phase0','vertex-phase31')),max(runs[n]['samples'][kind]['estimated_ms'] for n in ('vertex-phase0','vertex-phase31'))] for kind in ('position','lighting','texgen','normal')}
report={'xexSha256':manifest['XexSha256'],'framesPerRun':180,'runs':runs,'baselineDriftPercent':100*(after['render_ms']/ref['render_ms']-1),'vertexEstimateRangesMs':ranges,'limits':'CPU wall time in Xenia including waits, not GPU timestamps. Nested timers cannot be added indiscriminately. Vertex sampling uses 1/64 calls with two offsets and includes timing overhead. Counterfactual modes alter output, and their effects are not additive. CPU log equality checks sampled states, not full deterministic equivalence.'}
(folder/'analysis.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
lines=['# Diagnostico atual da renderizacao','',f"Mesma XEX `{manifest['XexSha256']}`, dez execucoes de 180 frames de Mario/Link CPU em Battlefield no Xenia. Referencias antes e depois; pacote do usuario preservado.",'','| Teste | Logica ms | Render ms | Total ms | Reducao render contra referencias |','|---|---:|---:|---:|---:|']
for name,run in runs.items():
    p=run['profile'];lo,hi=run['renderReductionPercentRange'];lines.append(f"| {name} | {p['logic_ms']:.3f} | {p['render_ms']:.3f} | {p['frame_ms']:.3f} | {lo:.1f}% a {hi:.1f}% |")
lines+=['',f"Variacao entre referencias: {report['baselineDriftPercent']:.1f}% no render. Estados CPU amostrados coincidiram em todas as execucoes.",'','## Detalhamento com desenho normal','']
for k,v in runs['detail-visible']['detail'].items():lines.append(f'- {k}: {v}')
lines+=['','## Estimativas por vertice','']
for kind,(lo,hi) in ranges.items():lines.append(f'- {kind}: {lo:.3f} a {hi:.3f} ms/frame (duas fases de amostragem).')
lines+=['','## Interpretacao e limites','',report['limits'],'','packet inclui montagem GX original, atributos e transformacoes. submit inclui pipeline e chamadas de desenho; draw_api e parte de submit. upload inclui cache/decodificacao/alocacao/sampler. copy inclui readback e filtro; idle e filtro sao subconjuntos. simple-shader conserva preparacao TEV e troca o pixel shader; no-draw remove DrawPrimitiveUP, conservando montagem; white-textures ignora cache/decodificacao e altera pixels/cache; no-copy substitui a imagem copiada por cor neutra. Nenhum e uma otimizacao publicavel como esta.','', 'O custo de esconder Fighters inclui todos os trabalhos de seus callbacks graficos. A logica e amostrada separadamente. Nao foram medidos tempos internos GPU ou hardware Xbox 360.']
(root/'docs/render-isolation-current.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
print('\n'.join(lines[:18]));print('Vertex estimates:',ranges)
