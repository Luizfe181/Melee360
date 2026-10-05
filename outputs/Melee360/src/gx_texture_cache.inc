/* Cache decoded images, not GX sampler state. Compare actual source bytes so
 * rewritten EFB copies, animated images and palette updates remain visible. */
struct CachedTexture {
 IDirect3DTexture9* texture;const u8* source;unsigned width,height,format,levels,paletteFormat,paletteEntries,bytes,lastUse;
 std::vector<u8> image,palette;
};
std::vector<CachedTexture> textureCache;unsigned textureCacheBytes,textureCacheClock;
unsigned textureCacheBudget(){static const unsigned budget=GetFileAttributesA("game:\\gx-cache-32mb.flag")!=((DWORD)-1)?32*1024*1024:64*1024*1024;return budget;}
bool textureCached(IDirect3DTexture9* texture){for(unsigned i=0;i<textureCache.size();++i)if(textureCache[i].texture==texture)return true;return false;}
IDirect3DTexture9* findCachedTexture(unsigned w,unsigned h,unsigned fmt,unsigned levels,const u8* data,unsigned bytes,const Palette* palette){
 static bool contentOnly=GetFileAttributesA("game:\\gx-content-only-cache.flag")!=((DWORD)-1);
 for(unsigned pass=contentOnly?1:0;pass<2;++pass)for(unsigned i=0;i<textureCache.size();++i){CachedTexture& entry=textureCache[i];
  if(!contentOnly&&((pass==0)!=(entry.source==data)))continue;
  if(entry.width!=w||entry.height!=h||entry.format!=fmt||entry.levels!=levels||entry.image.size()!=bytes||entry.paletteEntries!=(palette?palette->entries:0)||entry.paletteFormat!=(palette?palette->format:0))continue;
  if(memcmp(&entry.image[0],data,bytes)||(palette&&memcmp(&entry.palette[0],&palette->data[0],palette->data.size())))continue;
  entry.lastUse=++textureCacheClock;if(gxProfile.enabled)++gxProfile.cacheHits;return entry.texture;
 }return 0;
}
void keepCachedTexture(IDirect3DTexture9* texture,unsigned w,unsigned h,unsigned fmt,unsigned levels,const u8* data,unsigned bytes,const Palette* palette,unsigned allocationBytes){
 static const unsigned entryLimit=GetFileAttributesA("game:\\gx-cache-small-limit.flag")!=((DWORD)-1)?256u:1024u;
 unsigned cost=allocationBytes+bytes+(palette?(unsigned)palette->data.size():0);if(cost>textureCacheBudget())return;
 // Retain borrowed textures until GX teardown, including references saved by probes.
 // At capacity, use the original uncached upload path instead of invalidating them.
 if(textureCacheBytes>textureCacheBudget()-cost||textureCache.size()>=entryLimit)return;
 CachedTexture entry;entry.texture=texture;entry.source=data;entry.width=w;entry.height=h;entry.format=fmt;entry.levels=levels;entry.paletteFormat=palette?palette->format:0;entry.paletteEntries=palette?palette->entries:0;entry.bytes=cost;entry.lastUse=++textureCacheClock;entry.image.assign(data,data+bytes);if(palette)entry.palette=palette->data;textureCache.push_back(entry);textureCacheBytes+=cost;gxProfile.cacheEntries=(unsigned)textureCache.size();gxProfile.cacheBytes=textureCacheBytes;
}
void closeTextureCache(){
 /* All GX bindings have been detached before freeing retained resources. */
 while(!textureCache.empty()){IDirect3DTexture9* old=textureCache.back().texture;textureCache.pop_back();releaseTexture(old);}textureCacheBytes=textureCacheClock=0;
}

/* Opt-in adaptation of the existing binding. No eviction, pointer-only cache
 * key or palette shortcut: rewritten RAM is compared before every reuse. */
bool reuseBoundTexture(unsigned map,GXTexObj* object,const u8* data,unsigned bytes,unsigned w,unsigned h,unsigned format,bool mip,const Palette* palette){
 static const bool enabled=GetFileAttributesA("game:\\gx-texture-binding-reuse.flag")!=((DWORD)-1);
 if(!enabled||palette||gxProfile.whiteTextures||!boundValid[map]||!loadedTextures[map]||loadedTextures[map]==white||boundImages[map].size()!=bytes)return false;
 const GXTexObj* old=&boundDescriptors[map];
 if(GXGetTexObjWidth(old)!=w||GXGetTexObjHeight(old)!=h||GXGetTexObjFmt(old)!=format||((((const u8*)old)[31]&1)!=0)!=mip)return false;
 /* Max LOD determines the allocated mip chain. Sampler-only changes may
  * still reuse the image, but are reapplied by uploadTexture as before. */
 if(mip&&((old->dummy[1]>>8)&255)!=((object->dummy[1]>>8)&255))return false;
 if(memcmp(&boundImages[map][0],data,bytes))return false;
 if(gxProfile.enabled)++gxProfile.bindingReuses;
 return true;
}
