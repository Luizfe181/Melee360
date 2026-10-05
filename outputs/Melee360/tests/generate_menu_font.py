"""Rasterize UI glyphs at build time; does not ship the source font."""
import pathlib,sys
from PIL import Image,ImageFont,ImageDraw
font=ImageFont.truetype(r'C:\Windows\Fonts\consola.ttf',18)
image=Image.new('L',(256,144));draw=ImageDraw.Draw(image)
for i in range(96):draw.text(((i%16)*16+2,(i//16)*24),chr(i+32),font=font,fill=255)
data=image.tobytes()
lines=['// Generated UI glyph alpha atlas. Source font file is not bundled.','static const unsigned char Melee360MenuFontAlpha[36864] = {']
lines.extend(','.join(str(v) for v in data[i:i+128])+',' for i in range(0,len(data),128));lines.append('};')
pathlib.Path(sys.argv[1]).write_text('\n'.join(lines))
print('Generated menu font atlas')
