"""Regression for the full packed-frame stream, including frame 2650's aligned size."""
import json,pathlib,struct,sys
raw=pathlib.Path(sys.argv[1]).read_bytes()
u=lambda off:struct.unpack_from('>I',raw,off)[0]
assert raw[:4]==b'MTHP'
maximum=u(12);capacity=(maximum+4+31)&~31
offset,size=u(32),u(40);largest=(0,0);over_header=[]
for frame in range(u(28)):
    assert 8<=size<=capacity,(frame,size,capacity)
    assert offset+size<=len(raw),(frame,offset,size)
    assert raw[offset+4:offset+6]==b'\xff\xd8',frame
    if size>largest[0]:largest=(size,frame)
    if size>maximum:over_header.append(frame)
    following=u(offset);offset+=size;size=following
assert offset==len(raw),(offset,len(raw))
report=dict(frames=u(28),header_maximum=maximum,packed_capacity=capacity,largest_frame_bytes=largest[0],largest_frame_index=largest[1],frames_exceeding_header=over_header,stream_end=offset)
pathlib.Path(sys.argv[2]).write_text(json.dumps(report,indent=2));print(report)
