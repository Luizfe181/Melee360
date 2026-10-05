/* Original GX CPU functions and fog register translation. No GPU command stubs. */

#include <dolphin/gx.h>

#include <sysdolphin/baselib/debug.h>

#include <math.h>

#include <string.h>

#undef cosf

extern float cosf(float);

#define ASSERTMSGLINE(line,condition,message) HSD_ASSERTREPORT(line,condition,message)

#define ASSERTMSGLINEV(line,condition,...) HSD_ASSERTREPORT(line,condition,"GX argument validation")

GXBool __GXinBegin = GX_FALSE;

extern void Melee360GXRegisterTextureImage(GXTexObj*, const void*);

extern void Melee360GXRegisterPaletteImage(GXTlutObj*,const void*,u32,u32);

#define CHECK_GXBEGIN(line,name) ASSERTMSGLINE(line,!__GXinBegin,"GX object operation during primitive")

#define GET_REG_FIELD(reg,size,shift) ((int)((reg)>>(shift)) & ((1<<(size))-1))

#define SET_REG_FIELD(line,reg,size,shift,value) ((reg)=((reg)&~(((1u<<(size))-1u)<<(shift)))|(((unsigned int)(value)&((1u<<(size))-1u))<<(shift)))

static unsigned int Melee360LeadingZeros(unsigned int x){unsigned int n=0;if(!x)return 32;while(!(x&0x80000000U)){++n;x<<=1;}return n;}

#define __cntlzw Melee360LeadingZeros

extern void Melee360GXWriteFogRegister(u32);

#define GX_WRITE_RAS_REG(value) Melee360GXWriteFogRegister(value)

struct __GXLightObjInt_struct {
    u32 reserved[3];
    u32 Color;
    f32 a[3];
    f32 k[3];
    f32 lpos[3];
    f32 ldir[3];
};

void GXInitLightAttn(GXLightObj* lt_obj, f32 a0, f32 a1, f32 a2, f32 k0,
                     f32 k1, f32 k2)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x62, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x63, "GXInitLightAttn");
    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
    obj->k[0] = k0;
    obj->k[1] = k1;
    obj->k[2] = k2;
}

void GXInitLightAttnA(GXLightObj* lt_obj, f32 a0, f32 a1, f32 a2)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x70, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x71, "GXInitLightAttnA");
    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
}

void GXGetLightAttnA(GXLightObj* lt_obj, f32* a0, f32* a1, f32* a2)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x7A, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x7B, "GXGetLightAttnA");
    *a0 = obj->a[0];
    *a1 = obj->a[1];
    *a2 = obj->a[2];
}

void GXInitLightAttnK(GXLightObj* lt_obj, f32 k0, f32 k1, f32 k2)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x84, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x85, "GXInitLightAttnK");
    obj->k[0] = k0;
    obj->k[1] = k1;
    obj->k[2] = k2;
}

void GXGetLightAttnK(GXLightObj* lt_obj, f32* k0, f32* k1, f32* k2)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x8E, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x8F, "GXGetLightAttnK");
    *k0 = obj->k[0];
    *k1 = obj->k[1];
    *k2 = obj->k[2];
}

void GXInitLightSpot(GXLightObj* lt_obj, f32 cutoff, GXSpotFn spot_func)
{
    float a0, a1, a2;
    float r;
    float d;
    float cr;
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0xA7, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0xA9, "GXInitLightSpot");

    if (cutoff <= 0.0f || cutoff > 90.0f) {
        spot_func = GX_SP_OFF;
    }

    r = (3.1415927f * cutoff) / 180.0f;
    cr = cosf(r);
    switch (spot_func) {
    case GX_SP_FLAT:
        a0 = -1000.0f * cr;
        a1 = 1000.0f;
        a2 = 0.0f;
        break;
    case GX_SP_COS:
        a0 = -cr / (1.0f - cr);
        a1 = 1.0f / (1.0f - cr);
        a2 = 0.0f;
        break;
    case GX_SP_COS2:
        a0 = 0.0f;
        a1 = -cr / (1.0f - cr);
        a2 = 1.0f / (1.0f - cr);
        break;
    case GX_SP_SHARP:
        d = (1.0f - cr) * (1.0f - cr);
        a0 = (cr * (cr - 2.0f)) / d;
        a1 = 2.0f / d;
        a2 = -1.0f / d;
        break;
    case GX_SP_RING1:
        d = (1.0f - cr) * (1.0f - cr);
        a0 = (-4.0f * cr) / d;
        a1 = (4.0f * (1.0f + cr)) / d;
        a2 = -4.0f / d;
        break;
    case GX_SP_RING2:
        d = (1.0f - cr) * (1.0f - cr);
        a0 = 1.0f - ((2.0f * cr * cr) / d);
        a1 = (4.0f * cr) / d;
        a2 = -2.0f / d;
        break;
    case GX_SP_OFF:
    default:
        a0 = 1.0f;
        a1 = 0.0f;
        a2 = 0.0f;
        break;
    }
    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
}

void GXInitLightDistAttn(GXLightObj* lt_obj, f32 ref_dist, f32 ref_br,
                         GXDistAttnFn dist_func)
{
    f32 k0, k1, k2;
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0xF2, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0xF4, "GXInitLightDistAttn");

    if (ref_dist < 0.0f) {
        dist_func = GX_DA_OFF;
    }
    if (ref_br <= 0.0f || ref_br >= 1.0f) {
        dist_func = GX_DA_OFF;
    }

    switch (dist_func) {
    case GX_DA_GENTLE:
        k0 = 1.0f;
        k1 = (1.0f - ref_br) / (ref_br * ref_dist);
        k2 = 0.0f;
        break;
    case GX_DA_MEDIUM:
        k0 = 1.0f;
        k1 = (0.5f * (1.0f - ref_br)) / (ref_br * ref_dist);
        k2 = (0.5f * (1.0f - ref_br)) / (ref_br * ref_dist * ref_dist);
        break;
    case GX_DA_STEEP:
        k0 = 1.0f;
        k1 = 0.0f;
        k2 = (1.0f - ref_br) / (ref_br * ref_dist * ref_dist);
        break;
    case GX_DA_OFF:
    default:
        k0 = 1.0f;
        k1 = 0.0f;
        k2 = 0.0f;
        break;
    }

    obj->k[0] = k0;
    obj->k[1] = k1;
    obj->k[2] = k2;
}

void GXInitLightPos(GXLightObj* lt_obj, f32 x, f32 y, f32 z)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x129, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x12B, "GXInitLightPos");

    obj->lpos[0] = x;
    obj->lpos[1] = y;
    obj->lpos[2] = z;
}

void GXGetLightPos(GXLightObj* lt_obj, f32* x, f32* y, f32* z)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x134, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x136, "GXGetLightPos");

    *x = obj->lpos[0];
    *y = obj->lpos[1];
    *z = obj->lpos[2];
}

void GXInitLightDir(GXLightObj* lt_obj, f32 nx, f32 ny, f32 nz)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x149, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;

    obj->ldir[0] = -nx;
    obj->ldir[1] = -ny;
    obj->ldir[2] = -nz;
}

void GXGetLightDir(GXLightObj* lt_obj, f32* nx, f32* ny, f32* nz)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x155, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;

    *nx = -obj->ldir[0];
    *ny = -obj->ldir[1];
    *nz = -obj->ldir[2];
}

void GXInitSpecularDir(GXLightObj* lt_obj, f32 nx, f32 ny, f32 nz)
{
    float mag;
    float vx;
    float vy;
    float vz;
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x16F, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x170, "GXInitSpecularDir");

    vx = -nx;
    vy = -ny;
    vz = -nz + 1.0f;
    mag = 1.0f / sqrtf((vx * vx) + (vy * vy) + (vz * vz));
    obj->ldir[0] = vx * mag;
    obj->ldir[1] = vy * mag;
    obj->ldir[2] = vz * mag;
    obj->lpos[0] = -nx * 1048576.0f;
    obj->lpos[1] = -ny * 1048576.0f;
    obj->lpos[2] = -nz * 1048576.0f;
}

void GXInitSpecularDirHA(GXLightObj* lt_obj, f32 nx, f32 ny, f32 nz, f32 hx,
                         f32 hy, f32 hz)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x18E, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x18F, "GXInitSpecularHA");

    obj->ldir[0] = hx;
    obj->ldir[1] = hy;
    obj->ldir[2] = hz;
    obj->lpos[0] = -nx * 1048576.0f;
    obj->lpos[1] = -ny * 1048576.0f;
    obj->lpos[2] = -nz * 1048576.0f;
}

void GXInitLightColor(GXLightObj* lt_obj, GXColor color)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x1A8, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x1A9, "GXInitLightColor");

    obj->Color = (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}

void GXGetLightColor(GXLightObj* lt_obj, GXColor* color)
{
    struct __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(0x1B2, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct*) lt_obj;
    CHECK_GXBEGIN(0x1B3, "GXGetLightColor");

    color->r = (obj->Color >> 24) & 0xFF;
    color->g = (obj->Color >> 16) & 0xFF;
    color->b = (obj->Color >> 8) & 0xFF;
    color->a = obj->Color & 0xFF;
}

typedef struct __GXTexObjInt_struct {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void* userData;
    GXTexFmt fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} __GXTexObjInt;

typedef struct __GXTlutObjInt_struct {
    u32 tlut;
    u32 loadTlut0;
    u16 numEntries;
} __GXTlutObjInt;

static u8 GX2HWFiltConv[6] = { 0x00, 0x04, 0x01, 0x05, 0x02, 0x06 };

static void __GXGetTexTileShift(GXTexFmt fmt, u32* rowTileS, u32* colTileS)
{
    switch (fmt) {
    case GX_TF_I4:
    case 0x8:
    case GX_TF_CMPR:
    case GX_CTF_R4:
    case GX_CTF_Z4:
        *rowTileS = 3;
        *colTileS = 3;
        break;
    case GX_TF_I8:
    case GX_TF_IA4:
    case 0x9:
    case GX_TF_Z8:
    case GX_CTF_RA4:
    case GX_TF_A8:
    case GX_CTF_R8:
    case GX_CTF_G8:
    case GX_CTF_B8:
    case GX_CTF_Z8M:
    case GX_CTF_Z8L:
        *rowTileS = 3;
        *colTileS = 2;
        break;
    case GX_TF_IA8:
    case GX_TF_RGB565:
    case GX_TF_RGB5A3:
    case GX_TF_RGBA8:
    case 0xA:
    case GX_TF_Z16:
    case GX_TF_Z24X8:
    case GX_CTF_RA8:
    case GX_CTF_RG8:
    case GX_CTF_GB8:
    case GX_CTF_Z16L:
        *rowTileS = 2;
        *colTileS = 2;
        break;
    default:
        *rowTileS = *colTileS = 0;
        ASSERTMSGLINEV(0x184, 0, "%s: invalid texture format", "GX");
        break;
    }
}

u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap,
                       u8 max_lod)
{
    u32 tileShiftX;
    u32 tileShiftY;
    u32 tileBytes;
    u32 bufferSize;
    u32 nx;
    u32 ny;
    u32 level;

    ASSERTMSGLINEV(0x194, width <= 1024, "%s: width too large",
                   "GXGetTexBufferSize");
    ASSERTMSGLINEV(0x195, height <= 1024, "%s: height too large",
                   "GXGetTexBufferSize");

    __GXGetTexTileShift(format, &tileShiftX, &tileShiftY);
    if (format == GX_TF_RGBA8 || format == GX_TF_Z24X8) {
        tileBytes = 64;
    } else {
        tileBytes = 32;
    }
    if (mipmap == 1) {
        nx = 1 << (31 - __cntlzw(width));
        ASSERTMSGLINEV(0x1A7, width == nx, "%s: width must be a power of 2",
                       "GXGetTexBufferSize");
        ny = 1 << (31 - __cntlzw(height));
        ASSERTMSGLINEV(0x1AA, height == ny, "%s: height must be a power of 2",
                       "GXGetTexBufferSize");

        bufferSize = 0;
        for (level = 0; level < max_lod; level++) {
            nx = (width + (1 << tileShiftX) - 1) >> tileShiftX;
            ny = (height + (1 << tileShiftY) - 1) >> tileShiftY;
            bufferSize += tileBytes * (nx * ny);
            if (width == 1 && height == 1) {
                break;
            }
            width = (width > 1) ? width >> 1 : 1;
            height = (height > 1) ? height >> 1 : 1;
        }
    } else {
        nx = (width + (1 << tileShiftX) - 1) >> tileShiftX;
        ny = (height + (1 << tileShiftY) - 1) >> tileShiftY;
        bufferSize = nx * ny * tileBytes;
    }
    return bufferSize;
}

void __GetImageTileCount(enum _GXTexFmt fmt, u16 wd, u16 ht, u32* rowTiles,
                         u32* colTiles, u32* cmpTiles)
{
    u32 texRowShift;
    u32 texColShift;

    __GXGetTexTileShift(fmt, &texRowShift, &texColShift);
    if (wd == 0) {
        wd = 1;
    }
    if (ht == 0) {
        ht = 1;
    }
    *rowTiles = (wd + (1 << texRowShift) - 1) >> texRowShift;
    *colTiles = (ht + (1 << texColShift) - 1) >> texColShift;
    *cmpTiles = (fmt == GX_TF_RGBA8 || fmt == GX_TF_Z24X8) ? 2 : 1;
}

u16 GXGetTexObjWidth(const GXTexObj* to)
{
    const __GXTexObjInt* t = (const __GXTexObjInt*) to;

    ASSERTMSGLINE(0x36C, to, "Texture Object Pointer is null");
    return (u32) GET_REG_FIELD(t->image0, 10, 0) + 1;
}

u16 GXGetTexObjHeight(const GXTexObj* to)
{
    const __GXTexObjInt* t = (const __GXTexObjInt*) to;

    ASSERTMSGLINE(0x372, to, "Texture Object Pointer is null");
    return (u32) GET_REG_FIELD(t->image0, 10, 10) + 1;
}

GXTexFmt GXGetTexObjFmt(const GXTexObj* to)
{
    const __GXTexObjInt* t = (const __GXTexObjInt*) to;

    ASSERTMSGLINE(0x378, to, "Texture Object Pointer is null");
    return t->fmt;
}

void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height,
                  GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t,
                  u8 mipmap)
{
    u32 imageBase;
    u32 maxLOD;
    u16 rowT;
    u16 colT;
    u32 rowC;
    u32 colC;
    __GXTexObjInt* t = (__GXTexObjInt*) obj;

    ASSERTMSGLINE(0x1FD, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x1FF, "GXInitTexObj");
    ASSERTMSGLINEV(0x200, width <= 1024, "%s: width too large",
                   "GXInitTexObj");
    ASSERTMSGLINEV(0x201, height <= 1024, "%s: height too large",
                   "GXInitTexObj");
    ASSERTMSGLINEV(0x203, !(format & 0x20), "%s: invalid texture format",
                   "GXInitTexObj");
#if DEBUG
    if (wrap_s != GX_CLAMP || mipmap != 0) {
        u32 mask = 1 << (31 - __cntlzw(width));
        ASSERTMSGLINEV(0x20D, width == mask, "%s: width must be a power of 2",
                       "GXInitTexObj");
    }
    if (wrap_t != GX_CLAMP || mipmap != 0) {
        u32 mask = 1 << (31 - __cntlzw(height));
        ASSERTMSGLINEV(0x212, height == mask,
                       "%s: height must be a power of 2", "GXInitTexObj");
    }
#endif
    memset(t, 0, 0x20);
    SET_REG_FIELD(0x220, t->mode0, 2, 0, wrap_s);
    SET_REG_FIELD(0x221, t->mode0, 2, 2, wrap_t);
    SET_REG_FIELD(0x222, t->mode0, 1, 4, 1);
    if (mipmap != 0) {
        u8 lmax;
        t->flags |= 1;
        if (format - 8 <= 2U) {
            t->mode0 = (t->mode0 & 0xFFFFFF1F) | 0xA0;
        } else {
            t->mode0 = (t->mode0 & 0xFFFFFF1F) | 0xC0;
        }
        if (width > height) {
            maxLOD = 31 - __cntlzw(width);
        } else {
            maxLOD = 31 - __cntlzw(height);
        }
        lmax = 16.0f * maxLOD;
        SET_REG_FIELD(0x234, t->mode1, 8, 8, lmax);
    } else {
        t->mode0 = (t->mode0 & 0xFFFFFF1F) | 0x80;
    }
    t->fmt = format;
    SET_REG_FIELD(0x240, t->image0, 10, 0, width - 1);
    SET_REG_FIELD(0x241, t->image0, 10, 10, height - 1);
    SET_REG_FIELD(0x242, t->image0, 4, 20, format & 0xF);
    ASSERTMSGLINEV(0x248, ((u32) image_ptr & 0x1F) == 0,
                   "%s: %s pointer not aligned to 32B", "GXInitTexObj",
                   "image");
    imageBase = (u32) ((u32) image_ptr >> 5) & 0x01FFFFFF;
    SET_REG_FIELD(0x24A, t->image3, 21, 0, imageBase);
    switch (format & 0xF) {
    case 0:
    case 8:
        t->loadFmt = 1;
        rowT = 3;
        colT = 3;
        break;
    case 1:
    case 2:
    case 9:
        t->loadFmt = 2;
        rowT = 3;
        colT = 2;
        break;
    case 3:
    case 4:
    case 5:
    case 10:
        t->loadFmt = 2;
        rowT = 2;
        colT = 2;
        break;
    case 6:
        t->loadFmt = 3;
        rowT = 2;
        colT = 2;
        break;
    case 14:
        t->loadFmt = 0;
        rowT = 3;
        colT = 3;
        break;
    default:
        ASSERTMSGLINEV(0x275, 0, "%s: invalid texture format",
                       "GXPreLoadEntireTexture");
        t->loadFmt = 2;
        rowT = 2;
        colT = 2;
        break;
    }
    rowC = (width + (1 << rowT) - 1) >> rowT;
    colC = (height + (1 << colT) - 1) >> colT;
    t->loadCnt = (rowC * colC) & 0x7FFF;
    t->flags |= 2;
    Melee360GXRegisterTextureImage(obj, image_ptr);
}

void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height,
                    GXTexFmt format, GXTexWrapMode wrap_s,
                    GXTexWrapMode wrap_t, u8 mipmap, u32 tlut_name)
{
    __GXTexObjInt* t = (__GXTexObjInt*) obj;

    ASSERTMSGLINE(0x29B, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x29D, "GXInitTexObjCI");
    GXInitTexObj(obj, image_ptr, width, height, format, wrap_s, wrap_t,
                 mipmap);
    t->flags &= 0xFFFFFFFD;
    t->tlutName = tlut_name;
}

void GXInitTexObjData(GXTexObj* obj, void* image_ptr)
{
    u32 imageBase;
    __GXTexObjInt* t = (__GXTexObjInt*) obj;

    ASSERTMSGLINE(0x2F9, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x2FB, "GXInitTexObjData");
    ASSERTMSGLINEV(0x2FE, ((u32) image_ptr & 0x1F) == 0,
                   "%s: %s pointer not aligned to 32B", "GXInitTexObjData",
                   "image");
    imageBase = ((u32) image_ptr >> 5) & 0x01FFFFFF;
    SET_REG_FIELD(0x301, t->image3, 21, 0, imageBase);
    Melee360GXRegisterTextureImage(obj, image_ptr);
}

void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
                     f32 min_lod, f32 max_lod, f32 lod_bias, u8 bias_clamp,
                     u8 do_edge_lod, GXAnisotropy max_aniso)
{
    u8 lbias;
    u8 lmin;
    u8 lmax;
    __GXTexObjInt* t = (__GXTexObjInt*) obj;

    ASSERTMSGLINE(0x2C2, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x2C4, "GXInitTexObjLOD");

    if (lod_bias < -4.0f) {
        lod_bias = -4.0f;
    } else if (lod_bias >= 4.0f) {
        lod_bias = 3.99f;
    }
    lbias = 32.0f * lod_bias;
    SET_REG_FIELD(0x2CE, t->mode0, 8, 9, lbias);
    SET_REG_FIELD(0x2CF, t->mode0, 1, 4, (mag_filt == GX_LINEAR) ? 1 : 0);
    ASSERTMSGLINE(0x2D1, (u32) min_filt <= 5,
                  "GXInitTexObjLOD: invalid min_filt value");
    SET_REG_FIELD(0x2D2, t->mode0, 3, 5, GX2HWFiltConv[min_filt]);
    SET_REG_FIELD(0x2D3, t->mode0, 1, 8, do_edge_lod ? 0 : 1);
    t->mode0 &= 0xFFFDFFFF;
    t->mode0 &= 0xFFFBFFFF;
    SET_REG_FIELD(0x2D6, t->mode0, 2, 19, max_aniso);
    SET_REG_FIELD(0x2D7, t->mode0, 1, 21, bias_clamp);
    if (min_lod < 0.0f) {
        min_lod = 0.0f;
    } else if (min_lod > 10.0f) {
        min_lod = 10.0f;
    }
    lmin = 16.0f * min_lod;
    if (max_lod < 0.0f) {
        max_lod = 0.0f;
    } else if (max_lod > 10.0f) {
        max_lod = 10.0f;
    }
    lmax = 16.0f * max_lod;
    SET_REG_FIELD(0x2E5, t->mode1, 8, 0, lmin);
    SET_REG_FIELD(0x2E6, t->mode1, 8, 8, lmax);
}

void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, GXTlutFmt fmt,
                   u16 n_entries)
{
    __GXTlutObjInt* t = (__GXTlutObjInt*) tlut_obj;

    ASSERTMSGLINE(0x452, tlut_obj, "TLut Object Pointer is null");
    CHECK_GXBEGIN(0x453, "GXInitTlutObj");
    ASSERTMSGLINEV(0x456, n_entries <= 0x4000,
                   "%s: number of entries exceeds maximum", "GXInitTlutObj");
    ASSERTMSGLINEV(0x458, ((u32) lut & 0x1F) == 0,
                   "%s: %s pointer not aligned to 32B", "GXInitTlutObj",
                   "Tlut");
    t->tlut = 0;
    SET_REG_FIELD(0x45B, t->tlut, 2, 10, fmt);
    SET_REG_FIELD(0x45C, t->loadTlut0, 21, 0, ((u32) lut & 0x3FFFFFFF) >> 5);
    SET_REG_FIELD(0x45D, t->loadTlut0, 8, 24, 0x64);
    t->numEntries = n_entries;
    Melee360GXRegisterPaletteImage(tlut_obj,lut,fmt,n_entries);
}

void GXInitFogAdjTable(GXFogAdjTable* table, u16 width, f32 projmtx[4][4])
{
    f32 xi;
    f32 iw;
    f32 rangeVal;
    f32 nearZ;
    f32 sideX;
    u32 i;

    CHECK_GXBEGIN(0xCE, "GXInitFogAdjTable");
    ASSERTMSGLINE(0xCF, table != NULL,
                  "GXInitFogAdjTable: table pointer is null");
    ASSERTMSGLINE(0xD0, width <= 640,
                  "GXInitFogAdjTable: invalid width value");

    if (0.0 == projmtx[3][3]) {
        nearZ = projmtx[2][3] / (projmtx[2][2] - 1.0f);
        sideX = (nearZ * (1.0f + projmtx[0][2])) / projmtx[0][0];
    } else {
        nearZ = (1.0f + projmtx[2][3]) / projmtx[2][2];
        sideX = -(projmtx[0][3] - 1.0f) / projmtx[0][0];
    }

    iw = 2.0f / width;
    for (i = 0; i < 10; i++) {
        xi = (i + 1) << 5;
        xi *= iw;
        xi *= sideX;
        rangeVal = sqrtf(1.0f + ((xi * xi) / (nearZ * nearZ)));
        table->r[i] = (u32) (256.0f * rangeVal) & 0xFFF;
    }
}

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz,
              GXColor color)
{
    u32 fogclr;
    u32 fog0;
    u32 fog1;
    u32 fog2;
    u32 fog3;
    f32 A;
    f32 B;
    f32 B_mant;
    f32 C;
    f32 a;
    f32 c;
    u32 B_expn;
    u32 b_m;
    u32 b_s;
    u32 a_hex;
    u32 c_hex;

    CHECK_GXBEGIN(0x6E, "GXSetFog");

    ASSERTMSGLINE(0x70, farz >= 0.0f,
                  "GXSetFog: The farz should be positive value");
    ASSERTMSGLINE(0x71, farz >= nearz,
                  "GXSetFog: The farz should be larger than nearz");

    if (farz == nearz || endz == startz) {
        A = 0.0f;
        B = 0.5f;
        C = 0.0f;
    } else {
        A = (farz * nearz) / ((farz - nearz) * (endz - startz));
        B = farz / (farz - nearz);
        C = startz / (endz - startz);
    }

    B_mant = B;
    B_expn = 0;
    while (B_mant > 1.0) {
        B_mant *= 0.5f;
        B_expn++;
    }
    while (B_mant > 0.0f && B_mant < 0.5) {
        B_mant *= 2.0f;
        B_expn--;
    }

    a = A / (f32) (1 << (B_expn + 1));
    b_m = 8.388638e6f * B_mant;
    b_s = B_expn + 1;
    c = C;

    fog1 = 0;
    SET_REG_FIELD(0x94, fog1, 24, 0, b_m);
    SET_REG_FIELD(0x95, fog1, 8, 24, 0xEF);

    fog2 = 0;
    SET_REG_FIELD(0x98, fog2, 5, 0, b_s);
    SET_REG_FIELD(0x99, fog2, 8, 24, 0xF0);

    a_hex = *(u32*) &a;
    c_hex = *(u32*) &c;

    fog0 = 0;
    SET_REG_FIELD(0xA0, fog0, 11, 0, (a_hex >> 12) & 0x7FF);
    SET_REG_FIELD(0xA1, fog0, 8, 11, (a_hex >> 23) & 0xFF);
    SET_REG_FIELD(0xA2, fog0, 1, 19, (a_hex >> 31));
    SET_REG_FIELD(0xA3, fog0, 8, 24, 0xEE);

    fog3 = 0;
    SET_REG_FIELD(0xA6, fog3, 11, 0, (c_hex >> 12) & 0x7FF);
    SET_REG_FIELD(0xA7, fog3, 8, 11, (c_hex >> 23) & 0xFF);
    SET_REG_FIELD(0xA8, fog3, 1, 19, (c_hex >> 31));
    SET_REG_FIELD(0xA9, fog3, 1, 20, 0);
    SET_REG_FIELD(0xAA, fog3, 3, 21, type);
    SET_REG_FIELD(0xAB, fog3, 8, 24, 0xF1);

    fogclr = 0;
    SET_REG_FIELD(0xAE, fogclr, 8, 0, color.b);
    SET_REG_FIELD(0xAF, fogclr, 8, 8, color.g);
    SET_REG_FIELD(0xB0, fogclr, 8, 16, color.r);
    SET_REG_FIELD(0xB1, fogclr, 8, 24, 0xF2);

    GX_WRITE_RAS_REG(fog0);
    GX_WRITE_RAS_REG(fog1);
    GX_WRITE_RAS_REG(fog2);
    GX_WRITE_RAS_REG(fog3);
    GX_WRITE_RAS_REG(fogclr);
    /* Register writes update the native shader state, not a GX FIFO. */
}

void GXSetFogRangeAdj(GXBool enable, u16 center, GXFogAdjTable* table)
{
    u32 i;
    u32 range_adj;
    u32 range_c;

    CHECK_GXBEGIN(0x106, "GXSetFogRangeAdj");

    if (enable) {
        ASSERTMSGLINE(0x109, table != NULL,
                      "GXSetFogRangeAdj: table pointer is null");
        for (i = 0; i < 10; i += 2) {
            range_adj = 0;
            SET_REG_FIELD(0x10D, range_adj, 12, 0, table->r[i]);
            SET_REG_FIELD(0x10E, range_adj, 12, 12, table->r[i + 1]);
            SET_REG_FIELD(0x10F, range_adj, 8, 24, (i >> 1) + 0xE9);
            GX_WRITE_RAS_REG(range_adj);
        }
    }
    range_c = 0;
    SET_REG_FIELD(0x115, range_c, 10, 0, center + 342);
    SET_REG_FIELD(0x116, range_c, 1, 10, enable);
    SET_REG_FIELD(0x117, range_c, 8, 24, 0xE8);
    GX_WRITE_RAS_REG(range_c);
    /* Register writes update the native shader state, not a GX FIFO. */
}

u32 GXCompressZ16(u32 z24, GXZFmt16 zfmt)
{
    u32 z16;
    u32 z24n;
    s32 exp;
    s32 shift;
#if DEBUG
#define temp exp
#else
    s32 temp;
    u8 unused[4];
#endif

    z24n = ~(z24 << 8);
    temp = __cntlzw(z24n);
    switch (zfmt) {
    case GX_ZC_LINEAR:
        z16 = (z24 >> 8) & 0xFFFF;
        break;
    case GX_ZC_NEAR:
        if (temp > 3) {
            exp = 3;
        } else {
            exp = temp;
        }
        if (exp == 3) {
            shift = 7;
        } else {
            shift = 9 - exp;
        }
        z16 = ((z24 >> shift) & 0x3FFF & ~0xFFFFC000) | (exp << 14);
        break;
    case GX_ZC_MID:
        if (temp > 7) {
            exp = 7;
        } else {
            exp = temp;
        }
        if (exp == 7) {
            shift = 4;
        } else {
            shift = 10 - exp;
        }
        z16 = ((z24 >> shift) & 0x1FFF & ~0xFFFFE000) | (exp << 13);
        break;
    case GX_ZC_FAR:
        if (temp > 12) {
            exp = 12;
        } else {
            exp = temp;
        }
        if (exp == 12) {
            shift = 0;
        } else {
            shift = 11 - exp;
        }
        z16 = ((z24 >> shift) & 0xFFF & ~0xFFFFF000) | (exp << 12);
        break;
    default:
        OSPanic(__FILE__, 0x3B0, "GXCompressZ16: Invalid Z format\n");
        break;
    }
    return z16;
}

u32 GXDecompressZ16(u32 z16, GXZFmt16 zfmt)
{
    u32 z24;
    u32 cb1;
    long exp;
    long shift;

    cb1;
    cb1;
    cb1;
    z16;
    z16;
    z16; // needed to match

    switch (zfmt) {
    case GX_ZC_LINEAR:
        z24 = (z16 << 8) & 0xFFFF00;
        break;
    case GX_ZC_NEAR:
        exp = (z16 >> 14) & 3;
        if (exp == 3) {
            shift = 7;
        } else {
            shift = 9 - exp;
        }
        cb1 = -1 << (24 - exp);
        z24 = (cb1 | ((z16 & 0x3FFF) << shift)) & 0xFFFFFF;
        break;
    case GX_ZC_MID:
        exp = (z16 >> 13) & 7;
        if (exp == 7) {
            shift = 4;
        } else {
            shift = 10 - exp;
        }
        cb1 = -1 << (24 - exp);
        z24 = (cb1 | ((z16 & 0x1FFF) << shift)) & 0xFFFFFF;
        break;
    case GX_ZC_FAR:
        exp = (z16 >> 12) & 0xF;
        if (exp == 12) {
            shift = 0;
        } else {
            shift = 11 - exp;
        }
        cb1 = -1 << (24 - exp);
        z24 = (cb1 | ((z16 & 0xFFF) << shift)) & 0xFFFFFF;
        break;
    default:
        OSPanic(__FILE__, 0x3E2, "GXDecompressZ16: Invalid Z format\n");
        break;
    }
    return z24;
}

GXRenderModeObj GXNtsc480Int = { 0,
                                 640,
                                 480,
                                 480,
                                 40,
                                 0,
                                 640,
                                 480,
                                 1,
                                 0,
                                 0,
                                 { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                                   6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
                                 { 0, 0, 21, 22, 21, 0, 0 } };

GXRenderModeObj GXNtsc480IntDf = { 0,
                                   640,
                                   480,
                                   480,
                                   40,
                                   0,
                                   640,
                                   480,
                                   1,
                                   0,
                                   0,
                                   { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                                     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
                                   { 8, 8, 10, 12, 10, 8, 8 } };

GXRenderModeObj GXNtsc480Prog = { 2,
                                  640,
                                  480,
                                  480,
                                  40,
                                  0,
                                  640,
                                  480,
                                  0,
                                  0,
                                  0,
                                  { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                                    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
                                  { 0, 0, 21, 22, 21, 0, 0 } };

GXRenderModeObj GXNtsc480ProgAa = { 2,
                                    640,
                                    242,
                                    480,
                                    40,
                                    0,
                                    640,
                                    480,
                                    0,
                                    0,
                                    1,
                                    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10,
                                      9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
                                    { 4, 8, 12, 16, 12, 8, 4 } };

GXRenderModeObj GXNtsc480IntAa = { 0,
                                   640,
                                   242,
                                   480,
                                   40,
                                   0,
                                   640,
                                   480,
                                   1,
                                   0,
                                   1,
                                   { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10,
                                     9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
                                   { 4, 8, 12, 16, 12, 8, 4 } };

typedef char Melee360GXLightLayout[(sizeof(struct __GXLightObjInt_struct)==sizeof(GXLightObj))?1:-1];
typedef char Melee360GXTextureLayout[(sizeof(__GXTexObjInt)==sizeof(GXTexObj))?1:-1];
