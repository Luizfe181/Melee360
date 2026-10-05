"""Pin free Dolphin coefficients; emit immutable SRC conformance vectors."""
from pathlib import Path
import struct, hashlib, json
project = Path(__file__).resolve().parents[1]
raw = (project/'third_party/dolphin/dsp_coef.bin').read_bytes()
assert hashlib.sha256(raw).hexdigest() == 'd7741279c2e8ec5c5fb318f8fbdd6de6bf583520d288e836a5383233a4238179'
coefs = struct.unpack('>2048h', raw)
header = ['/* SPDX-License-Identifier: GPL-2.0-or-later',
          ' * Free DSP coefficients from dolphin-emu/dolphin, commit',
          ' * eb236466c4f0ec8bef619add0972353d3996fe6c. See third_party/dolphin. */',
          'static const s16 axPolyphaseCoefficients[1536] = {']
for n in range(0,1536,16): header.append(' '+','.join(map(str,coefs[n:n+16]))+',')
header += ['};']
(project/'src/ax_src_coefficients.inc').write_text('\n'.join(header)+'\n')
# Deliberately queue-based model, separate from native rolling-history code.
signal = [32767,-32768,1000,-2000,12000,-9000,0,16384]
cases = []
for bank in range(3):
    for ratio,initial in [(0,65535),(32768,12345),(65536,0),(98304,32768),(262144,65535)]:
        history = [300,-400,500,-600]
        phase,position = initial,0
        output=[]
        for _ in range(32):
            phase += ratio
            while phase >= 65536:
                history = history[1:] + [signal[position%8]]
                position += 1
                phase -= 65536
            start = bank*512+(phase>>9)*4
            value=sum(x*c for x,c in zip(history,coefs[start:start+4]))>>15
            output.append(max(-32768,min(32767,value)))
        cases.append(dict(bank=bank,ratio=ratio,initial=initial,phase=phase,position=position%8,history=history,output=output))
lines=['/* Generated fixed vectors; reference: diagnostics/generate_ax_src.py. */',
       'typedef struct {u16 bank;u32 ratio;u16 initial,phase,position;s16 history[4],output[32];} AXSrcVector;',
       'static const s16 axSrcInput[8]={'+','.join(map(str,signal))+'};',
       'static const AXSrcVector axSrcVectors[15]={']
for c in cases:
    lines.append('{%d,%d,%d,%d,%d,{%s},{%s}},'%(c['bank'],c['ratio'],c['initial'],c['phase'],c['position'],','.join(map(str,c['history'])),','.join(map(str,c['output']))))
lines.append('};')
(project/'src/ax_src_vectors.inc').write_text('\n'.join(lines)+'\n')
(project/'logs/ax-src-reference-vectors.json').write_text(json.dumps({'coefficientSha256':hashlib.sha256(raw).hexdigest(),'cases':cases},indent=2)+'\n')
print('Generated 3 banks / 128 phases / 4 taps and 15 fixed reference vectors.')

linear=[]
for ratio,initial in [(0,0),(0,65535),(32768,12345),(65536,0),(98304,32768),(262144,65535)]:
    history=[300,-400,500,-600];phase=initial;position=0;output=[]
    for _ in range(32):
        phase+=ratio
        while phase>=65536:
            history=history[1:]+[signal[position%8]];position+=1;phase-=65536
        output.append((history[0]*(65536-phase)+history[1]*phase)>>16 if phase else history[0])
    linear.append(dict(bank=0,ratio=ratio,initial=initial,phase=phase,position=position%8,history=history,output=output))
lines=['static const AXSrcVector axLinearVectors[6]={']
for c in linear:
    lines.append('{%d,%d,%d,%d,%d,{%s},{%s}},'%(c['bank'],c['ratio'],c['initial'],c['phase'],c['position'],','.join(map(str,c['history'])),','.join(map(str,c['output']))))
lines.append('};')
with (project/'src/ax_src_vectors.inc').open('a') as f:f.write('\n'.join(lines)+'\n')
(project/'logs/ax-linear-reference-vectors.json').write_text(json.dumps({'reference':'Dolphin AXVoice.h ResampleAudio linear four-sample history','cases':linear},indent=2)+'\n')
