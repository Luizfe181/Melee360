import collections,json,pathlib,subprocess,sys
assets,exe,inventory=map(pathlib.Path,sys.argv[1:4])
reports=[]
for scene in json.loads(inventory.read_text()):
    statuses=collections.Counter();verts=0;unsupported=[]
    for mesh in scene['meshes']:
        result=subprocess.run([str(exe),str(assets/scene['archive']),str(mesh['offset'])],capture_output=True,text=True,check=True)
        status,n,feature=map(int,result.stdout.split());statuses[status]+=1;verts+=n
        if status<0: unsupported.append(dict(mesh=mesh['offset'],feature=feature))
    report=dict(archive=scene['archive'],statuses=dict(statuses),triangle_vertices=verts,unsupported=unsupported)
    reports.append(report);print(report)
(inventory.parent/'menu-mesh-decode.json').write_text(json.dumps(reports,indent=2))
