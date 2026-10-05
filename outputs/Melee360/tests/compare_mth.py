"""Compare raw-MTH portable decoder with independent Pillow/libjpeg decoding."""
import io, struct, sys, json
from pathlib import Path
import numpy as np
from PIL import Image
root=Path(__file__).resolve().parents[1]
movie=Path(sys.argv[1])
frames=[int(v) for v in sys.argv[2].split(',')] if len(sys.argv)>2 else [0,900,1800,3035]
prefix=sys.argv[3] if len(sys.argv)>3 else 'intro'
results=[]
with movie.open('rb') as f:
    header=f.read(64)
    offset=struct.unpack_from('>I',header,32)[0]
    size=struct.unpack_from('>I',header,40)[0]
    for index in range(max(frames)+1):
        f.seek(offset); packed=f.read(size)
        if len(packed)!=size: raise RuntimeError('Truncated movie')
        if index in frames:
            raw=packed[4:]
            pos=2
            while True:
                if raw[pos]!=255: raise RuntimeError('Invalid marker')
                marker=raw[pos+1]; length=struct.unpack_from('>H',raw,pos+2)[0]
                pos+=2+length
                if marker==0xDA: break
            # MTH omits JPEG entropy stuffing; insert it for the independent decoder.
            end=raw.rfind(b'\xff\xd9')
            if end<pos: end=len(raw)
            jpeg=raw[:pos]+raw[pos:end].replace(b'\xff',b'\xff\x00')+b'\xff\xd9'
            ref=Image.open(io.BytesIO(jpeg)); ref.load()
            decoded=Image.open(root/'build'/'host-tests'/f'{prefix}-{index}.ppm')
            # Compare against nearest chroma reconstruction used on Xbox.
            ref.draft('YCbCr', ref.size)
            a=np.asarray(ref.convert('RGB'),dtype=np.int16)
            b=np.asarray(decoded,dtype=np.int16)
            delta=np.abs(a-b)
            results.append(dict(frame=index,mean_absolute_error=float(delta.mean()),
                                percentile99=float(np.percentile(delta,99)),maximum=int(delta.max())))
            decoded.save(root/'logs'/f'{prefix}-frame-{index}.png')
            if delta.mean()>3.0 or np.percentile(delta,99)>15:
                raise RuntimeError(f'Image difference too large: {results[-1]}')
        offset+=size
        size=struct.unpack_from('>I',packed)[0]
(root/'logs'/('mth-decoder-comparison.json' if prefix=='intro' else prefix+'-decoder-comparison.json')).write_text(json.dumps(results,indent=2))
print(json.dumps(results,indent=2))
