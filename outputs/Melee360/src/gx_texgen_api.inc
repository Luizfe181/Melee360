extern "C" void GXSetNumTexGens(u8 count){require(!__GXinBegin&&count<=8);numTexGenerators=count;texGeneratorsActive=true;}
extern "C" void GXSetTexCoordGen2(GXTexCoordID destination,GXTexGenType type,GXTexGenSrc source,u32 matrix,GXBool normalize,u32 post){
 require(!__GXinBegin&&destination>=GX_TEXCOORD0&&destination<=GX_TEXCOORD7&&(normalize==GX_FALSE||normalize==GX_TRUE)&&(type==GX_TG_MTX2x4||type==GX_TG_MTX3x4||type==GX_TG_SRTG||(type>=GX_TG_BUMP0&&type<=GX_TG_BUMP7)));
 require(type>=GX_TG_BUMP0&&type<=GX_TG_BUMP7?(source>=GX_TG_TEXCOORD0&&source<=GX_TG_TEXCOORD6&&source-GX_TG_TEXCOORD0<destination):type==GX_TG_SRTG?(source==GX_TG_COLOR0||source==GX_TG_COLOR1):(source==GX_TG_POS||source==GX_TG_NRM||source==GX_TG_BINRM||source==GX_TG_TANGENT||(source>=GX_TG_TEX0&&source<=GX_TG_TEX7)));
 require(matrix==GX_IDENTITY||(matrix<=57&&matrix%3==0));require(post==GX_PTIDENTITY||(post>=64&&post<=121&&(post-64)%3==0));
 TexGenerator value={true,type,source,matrix,post,normalize!=GX_FALSE};texGenerators[destination]=value;
}
