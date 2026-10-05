/* GX line/point primitives expanded in homogeneous clip coordinates.
 * No geometry shader is required on Xenon. Widths are original sixth-pixels. */
namespace {
u8 lineWidth=6,pointSize=6;GXTexOffset lineOffset=GX_TO_ZERO,pointOffset=GX_TO_ZERO;
bool lineTexOffsets[8],pointTexOffsets[8];
bool validPrimitive(unsigned primitive,unsigned count){
    return count&&((primitive==GX_TRIANGLES&&count%3==0)||(primitive==GX_QUADS&&count%4==0)||
        ((primitive==GX_TRIANGLESTRIP||primitive==GX_TRIANGLEFAN)&&count>=3)||
        (primitive==GX_LINES&&count%2==0)||(primitive==GX_LINESTRIP&&count>=2)||primitive==GX_POINTS);
}
float textureOffset(GXTexOffset offset){static const float values[]={0,1.f/16,1.f/8,1.f/4,1.f/2,1};return values[(int)offset];}
void offsetUV(Vertex& v,unsigned unit,float u,float t){float* coord=unit?v.extraUV[unit-1]:v.uv;coord[0]+=u*coord[2];coord[1]+=t*coord[2];}
void quadVertices(const Vertex& a,const Vertex& b,const Vertex& c,const Vertex& d){
    triangleVertices.push_back(a);triangleVertices.push_back(b);triangleVertices.push_back(c);
    triangleVertices.push_back(c);triangleVertices.push_back(b);triangleVertices.push_back(d);
}
Vertex interpolateRasterVertex(const Vertex& a,const Vertex& b,float t){
    Vertex result;const float* x=(const float*)&a;const float* y=(const float*)&b;float* z=(float*)&result;
    for(unsigned i=0;i<sizeof(Vertex)/sizeof(float);++i)z[i]=x[i]+(y[i]-x[i])*t;return result;
}
bool clipLineDepth(Vertex& a,Vertex& b){
    // Clip before dividing by w; leave lateral clipping to the GPU after expansion.
    for(int plane=0;plane<2;++plane){float x=plane?a.clip[3]-a.clip[2]:a.clip[2],y=plane?b.clip[3]-b.clip[2]:b.clip[2];
        if(x<0&&y<0)return false;if(x<0)a=interpolateRasterVertex(a,b,x/(x-y));else if(y<0)b=interpolateRasterVertex(a,b,x/(x-y));}
    return a.clip[3]>0&&b.clip[3]>0;
}
void expandPoint(const Vertex& input,float width,float height){
    if(!pointSize||input.clip[3]<=0)return;float dx=pointSize/(6.f*width)*input.clip[3],dy=pointSize/(6.f*height)*input.clip[3];
    Vertex tl=input,tr=input,bl=input,br=input;tl.clip[0]-=dx;tl.clip[1]+=dy;tr.clip[0]+=dx;tr.clip[1]+=dy;
    bl.clip[0]-=dx;bl.clip[1]-=dy;br.clip[0]+=dx;br.clip[1]-=dy;float offset=textureOffset(pointOffset);
    for(unsigned unit=0;unit<8;++unit)if(pointTexOffsets[unit]){offsetUV(tr,unit,offset,0);offsetUV(bl,unit,0,offset);offsetUV(br,unit,offset,offset);}
    quadVertices(tl,tr,bl,br);
}
void expandLine(Vertex a,Vertex b,float width,float height){
    if(!lineWidth||!clipLineDepth(a,b))return;
    float x=fabsf(b.clip[0]/b.clip[3]-a.clip[0]/a.clip[3])*width,y=fabsf(b.clip[1]/b.clip[3]-a.clip[1]/a.clip[3])*height;
    if(x==0&&y==0)return;float dx=y>x?lineWidth/(6.f*width):0,dy=y>x?0:-lineWidth/(6.f*height);
    Vertex al=a,ar=a,bl=b,br=b;al.clip[0]-=dx*a.clip[3];al.clip[1]-=dy*a.clip[3];ar.clip[0]+=dx*a.clip[3];ar.clip[1]+=dy*a.clip[3];
    bl.clip[0]-=dx*b.clip[3];bl.clip[1]-=dy*b.clip[3];br.clip[0]+=dx*b.clip[3];br.clip[1]+=dy*b.clip[3];float offset=textureOffset(lineOffset);
    for(unsigned unit=0;unit<8;++unit)if(lineTexOffsets[unit]){offsetUV(ar,unit,offset,0);offsetUV(br,unit,offset,0);}
    quadVertices(al,ar,bl,br);
}
void submitRaster(){
    float viewport[6];GXGetViewportv(viewport);require(viewport[2]>0&&viewport[3]>0);triangleVertices.clear();
    if(activePrimitive==GX_POINTS){triangleVertices.reserve(expected*6);for(unsigned i=0;i<vertices.size();++i)expandPoint(vertices[i],viewport[2],viewport[3]);}
    else {unsigned step=activePrimitive==GX_LINES?2:1;triangleVertices.reserve((expected/step)*6);for(unsigned i=0;i+1<vertices.size();i+=step)expandLine(vertices[i],vertices[i+1],viewport[2],viewport[3]);}
    if(!triangleVertices.empty()){DWORD cull;require(SUCCEEDED(device->GetRenderState(D3DRS_CULLMODE,&cull)));device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
        require(SUCCEEDED(drawDirect(D3DPT_TRIANGLELIST,(unsigned)triangleVertices.size()/3,&triangleVertices[0],sizeof(Vertex))));device->SetRenderState(D3DRS_CULLMODE,cull);}
    primitiveActive=false;
}
}
extern "C" void GXSetLineWidth(u8 width,GXTexOffset offset){require(!__GXinBegin&&offset>=GX_TO_ZERO&&offset<=GX_TO_ONE);lineWidth=width;lineOffset=offset;}
extern "C" void GXSetPointSize(u8 size,GXTexOffset offset){require(!__GXinBegin&&offset>=GX_TO_ZERO&&offset<=GX_TO_ONE);pointSize=size;pointOffset=offset;}
extern "C" void GXEnableTexOffsets(GXTexCoordID coord,u8 line,u8 point){require(!__GXinBegin&&coord>=GX_TEXCOORD0&&coord<=GX_TEXCOORD7&&line<=1&&point<=1);lineTexOffsets[coord]=line!=0;pointTexOffsets[coord]=point!=0;}
extern "C" void GXGetLineWidth(u8* width,GXTexOffset* offset){require(width&&offset);*width=lineWidth;*offset=lineOffset;}
extern "C" void GXGetPointSize(u8* size,GXTexOffset* offset){require(size&&offset);*size=pointSize;*offset=pointOffset;}
