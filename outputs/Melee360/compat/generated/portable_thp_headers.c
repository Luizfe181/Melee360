/* Original THP header/parser CPU path; Gekko IDCT is not compiled. */

#include <dolphin/thp/thp.h>

#include <string.h>

#define THPROUNDUP(a,b) ((((s32)(a))+((s32)(b)-1L))/((s32)(b)))

static char __THP420Error[] = "ERROR: THP only supports 4:2:0!!!\n";

static const u8 __THPJpegNaturalOrder[80] = {
    0,  1,  8,  16, 9,  2,  3,  10, 17, 24, 32, 25, 18, 11, 4,  5,
    12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13, 6,  7,  14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63,
    63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63
};

static const f64 __THPAANScaleFactor[8] = {
    1.0f, 1.387039845f, 1.306562965f, 1.175875602f,
    1.0f, 0.785694958f, 0.541196100f, 0.275899379f,
};

typedef struct THPVideoDecodeHeader {
    u16 xSize;
    u16 ySize;
} THPVideoDecodeHeader;

u8 THPDec_803310CC(THPFileInfo*);

s32 THPDec_8032F8D4(u8* data, THPDec_8032FD40_Data* out)
{
    u8 hSample[4];
    u8 vSample[4];
    u8 componentId[4];
    u8 quantizationSelector[4];
    u8 marker;
    u8 componentCount;
    u8 tag[5] = "JFIF";
    u8 i;
    u8 valid;
    u32 j;
    u16 length;

    valid = 0;
    memset(out, 0, 0xC);

    {
        u8 soi0 = *data++;
        u8 soi1 = *data++;

        if (soi0 != 0xFF || soi1 != 0xD8) {
            return 0;
        }
    }

    for (;;) {
        if (*data++ != 0xFF) {
            return 0;
        }

        while ((s8) *data == 0xFF) {
            data++;
        }
        marker = *data++;

        if (marker == 0xC0) {
            out->_pad = data[4] | (data[3] << 8);
            out->val1 = data[6] | (data[5] << 8);
            componentCount = data[7];
            data += 8;

            if (componentCount != 3) {
                return 0;
            }

            for (i = 0; i < componentCount; i++) {
                u8 factors;

                componentId[i] = *data++;
                factors = *data++;
                hSample[i] = (u8) (factors >> 4);
                vSample[i] = (u8) (factors & 0xF);
                quantizationSelector[i] = *data++;
            }

            if (hSample[0] / hSample[1] == 2 && hSample[0] / hSample[2] == 2) {
                if (vSample[0] / vSample[1] == 2 &&
                    vSample[0] / vSample[2] == 2)
                {
                    out->val2 = 4;
                } else if (vSample[0] == vSample[1] &&
                           vSample[0] == vSample[2])
                {
                    out->val2 = 2;
                }
            } else if (hSample[0] == hSample[1] && hSample[0] == hSample[2]) {
                if (vSample[0] == vSample[1] && vSample[0] == vSample[2]) {
                    out->val2 = 1;
                }
            } else {
                return 0;
            }
        } else if (marker == 0xE0) {
            length = *data++;
            length = (u16) ((length << 8) | *data++);
            for (i = 0; i < 5; i++) {
                componentCount = *data++;
                if (componentCount != tag[i]) {
                    return 0;
                }
            }
            valid = 1;
            for (j = 0; j < (u32) (length - 7); j++) {
                data++;
            }
        } else if (marker == 0xDA) {
            break;
        } else if (0xC0 <= marker && marker <= 0xFE) {
            length = data[1] | (data[0] << 8);
            data += 2;

            for (j = 0; j < (u32) (length - 2); j++) {
                data++;
            }
        }

        if (out->val2 != 0 && valid != 0) {
            break;
        }
    }

    return 1;
}

s32 THPDec_8032FD40(THPDec_8032FD40_Data* data, u16 num)
{
    s32 base = data->val0 + 0x4028;
    s32 a;
    if (data->val2 != 4) {
        OSReport(__THP420Error);
        return 0;
    }
    a = (data->val1 / 2) * (num / 2) * 2 + (data->val1 * num);
    base = base + a;
    return base;
}

THPFileInfo* THPVideoDecode(void* hdr, void* status_out, THPFileInfo* work,
                            void* data, THPDec_8032FD40_Data* desc)
{
    u8 done;
    THPFileInfo* info = work;
    THPVideoDecodeHeader* header = hdr;
    u8* statusOut = status_out;
    u8 status;
    s32 length;
    u32 i;

    memset(info, 0, 0x920);
    info->scratch = (u8*) info;
    info->scratch += 0x920;
    info->xSize = header->xSize;
    info->ySize = header->ySize;
    info->file = info->scanStart;
    info->cnt = 33;
    info->x8EC = 0;
    info->x8EE = 0;
    info->x8D2 = 0;
    info->x8E8 = 0;
    info->x8EA = 0;
    info->x7D = 0;
    info->dataStart = data;
    THPDec_803300E0(info);
    done = FALSE;
    info->file = info->dataStart;

    for (;;) {
        if ((*(info->file)++) != 0xFF) {
            goto _err_bad_syntax;
        }

        while (*info->file == 0xFF) {
            info->file++;
        }

        status = (*(info->file)++);

        if (status <= 0xD7) {
            if (status == 0xC4) {
                status = __THPReadHuffmanTableSpecification(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else if (status == 0xC0) {
                status = __THPReadFrameHeader(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else {
                *statusOut = 11;
                return NULL;
            }
        } else if (0xD8 <= status && status <= 0xDF) {
            if (status == 0xDD) {
                __THPRestartDefinition(info);
            } else if (status == 0xDB) {
                status = __THPReadQuantizationTable(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else if (status == 0xDA) {
                status = __THPReadScaneHeader(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
                done = TRUE;
                info->scanStart = info->file;
            } else if (status != 0xD8) {
                *statusOut = 11;
                return NULL;
            }
        } else if (0xE0 <= status) {
            if (status == 0xE0) {
                status = THPDec_80330158(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else if (0xE1 <= status && status <= 0xEF) {
                THPDec_803302EC(&info->file);
            } else if (status == 0xFE) {
                length = (info->file[0] << 8) | info->file[1];
                info->file += 2;
                for (i = 0; i < length - 2; i++) {
                    info->file++;
                }
            } else {
                *statusOut = 11;
                return NULL;
            }
        }

        if (done) {
            *statusOut = 0;
            return work;
        }
    }

_err_bad_syntax:
    *statusOut = 3;
    goto _err_exit;

_err_bad_status:
    *statusOut = status;

_err_exit:
    return NULL;
}

void THPDec_803300E0(THPFileInfo* info)
{
    u8* p;
    u8 i;

    p = (u8*) OSRoundUp32B((u32)info->scratch);
    info->scratch = p + 16 * 128;
    for (i = 0; i < 16; i++) {
        info->mcuBuffer[i] = (THPCoeff*) p;
        p += 128;
    }
}

u8 THPDec_80330158(THPFileInfo* info)
{
    u8 tag[5] = "JFIF";
    u16 length;
    u32 i;
    u8 xThumb;
    u8 yThumb;
    u16 version;
    u8 units;
    u32 segmentLength;

    length = (u16) ((info->file[0] << 8) | info->file[1]);
    info->file += 2;

    for (i = 0; i < 5; i++) {
        if (*(info->file)++ != tag[i]) {
            return 3;
        }
    }

    version = (u16) ((info->file[0] << 8) | info->file[1]);
    info->file += 2;
    units = *(info->file)++;
    info->file += 1;
    info->file += 1;
    info->file += 1;
    info->file += 1;

    xThumb = *(info->file)++;
    yThumb = *(info->file)++;

    if (xThumb != 0 || yThumb != 0) {
        return 7;
    }

    segmentLength = (u32) (info->file - info->dataStart);
    if (length + 4 != segmentLength) {
        return 8;
    }

    return 0;
}

s32 THPDec_803302EC(u8** data)
{
    u32 i;
    u8* ptr = *data;
    u16 high = ptr[0];
    u16 low = ptr[1];

    u16 count = (high << 8) | low;
    for (i = 0; i < count; i++) {
        (*data)++;
    }

    return 0;
}

static u8 __THPReadFrameHeader(THPFileInfo* info)
{
    u8 i;
    u8 j;
    u8 k;
    THPComponent* comp;
    u8 utmp8;
    u16 ySize;

    info->file += 2;

    utmp8 = (*(info->file)++);

    if (utmp8 != 8) {
        return 10;
    }

    info->yPixelSize = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    info->xPixelSize = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;

    info->nComponents = (*(info->file)++);
    if (info->nComponents != 3 && info->nComponents != 1) {
        return 12;
    }

    for (i = 0; i < info->nComponents; i++) {
        info->components[i].componentID = (*(info->file)++);
        utmp8 = (*(info->file)++);
        info->components[i].samplingH = (u8) (utmp8 >> 4);
        info->components[i].samplingV = (u8) (utmp8 & 0xF);
        info->components[i].quantizationTableSelector = (*(info->file)++);
    }

    info->samplingHMax = 1;
    info->samplingVMax = 1;
    for (j = 0; j < info->nComponents; j++) {
        comp = &info->components[j];
        info->samplingHMax = info->samplingHMax > comp->samplingH
                                 ? info->samplingHMax
                                 : comp->samplingH;
        info->samplingVMax = info->samplingVMax > comp->samplingV
                                 ? info->samplingVMax
                                 : comp->samplingV;
    }

    ySize = info->yPixelSize;
    info->x8D4 =
        (u16) THPROUNDUP(ySize, THPROUNDUP(ySize, info->samplingVMax * 8));
    for (k = 0; k < info->nComponents; k++) {
        info->components[k].x08 =
            THPROUNDUP(info->xPixelSize * info->components[k].samplingH,
                       info->samplingHMax);
        info->components[k].x0C =
            THPROUNDUP(info->yPixelSize * info->components[k].samplingV,
                       info->samplingVMax);
    }

    return 0;
}

static u8 __THPReadQuantizationTable(THPFileInfo* info)
{
    u16 length, id, i, row, col;
    f32 q_temp[64];

    length = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    length -= 2;

    for (;;) {
        id = (*(info->file)++);

        for (i = 0; i < 64; i++) {
            q_temp[__THPJpegNaturalOrder[i]] = (f32) (*(info->file)++);
        }

        info->validQuantTabs |= 1 << id;

        i = 0;
        for (row = 0; row < 8; row++) {
            for (col = 0; col < 8; col++) {
                info->quantTabs[id][i] = q_temp[i] * __THPAANScaleFactor[row] *
                                         __THPAANScaleFactor[col];
                i++;
            }
        }

        length -= 65;
        if (!length) {
            break;
        }
    }

    return 0;
}

static u8 __THPReadHuffmanTableSpecification(THPFileInfo* info)
{
    u8 t_class, id, i;
    u8 tab_index;
    u16 length, num_Vij;
    u8* huffmanBits;
    u8 result;

    length = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    length -= 2;

    for (;;) {
        i = (*(info->file)++);
        id = (u8) (i & 15);
        t_class = (u8) (i >> 4);
        huffmanBits = info->file;
        tab_index = (u8) ((id << 1) + t_class);
        num_Vij = 0;

        for (i = 0; i < 16; i++) {
            num_Vij += (*(info->file)++);
        }

        info->huffmanTabs[tab_index].bits = huffmanBits;
        info->huffmanTabs[tab_index].Vij = info->file;
        info->huffmanTabs[tab_index].numVij = num_Vij;
        info->file += num_Vij;
        result =
            __THPHuffGenerateSizeTable(info, tab_index, (int) huffmanBits);
        if (result) {
            return result;
        }
        result = __THPHuffGenerateCodeTable(info, tab_index);
        if (result) {
            return result;
        }
        __THPHuffGenerateDecoderTables(info, tab_index);

        info->validHuffmanTabs |= 1 << tab_index;
        length -= 17 + num_Vij;

        if (length == 0) {
            break;
        }
    }

    return 0;
}

static u8 __THPReadScaneHeader(THPFileInfo* info)
{
    u8 numComponents;
    u8 i;
    u8* ptr;
    info->file += 2;
    ptr = info->file;
    info->file++;
    numComponents = *ptr;

    if (numComponents != info->nComponents) {
        return 12;
    }

    for (i = 0; i < numComponents; i++) {
        u8 selectors;
        u16 blocksPerRow;
        u16 rows;
        s32 shift;

        selectors = *info->file++;
        selectors = *info->file++;

        info->components[i].DCTableSelector = (u8) (selectors >> 4);
        info->components[i].ACTableSelector = (u8) (selectors & 0xF);

        if (!(info->validHuffmanTabs & (1 << (selectors >> 4)))) {
            return 15;
        }
        if (!(info->validHuffmanTabs & (1 << ((selectors & 0xF) + 1)))) {
            return 15;
        }

        info->x74 = info->xSize;
        info->decompressedY = info->ySize;

        blocksPerRow = info->components[i].x08;
        rows = THPROUNDUP(info->decompressedY, info->x8D4);
        rows += (info->decompressedY % info->x8D4 == 0) ? 0 : 1;
        rows *= info->x8D4;
        shift = info->samplingVMax - info->components[i].samplingV;
        rows >>= shift;
        info->components[i].x10 = (uintptr_t) info->scratch;
        info->scratch += blocksPerRow * rows;
    }

    info->file += 3;
    return THPDec_803310CC(info);
}

static u8 __THPHuffGenerateSizeTable(THPFileInfo* info, u8 tab_index,
                                     int huffmanBits)
{
    u8* bits;
    s32 p;
    s32 l;
    s32 i;

    bits = (u8*) huffmanBits;

    p = 0;
    for (l = 1; l <= 16; l++) {
        p += bits[l - 1];
    }

    info->huffmanTabs[tab_index].sizeTab = (s8*) info->scratch;
    info->scratch += p + 1;

    p = 0;
    for (l = 1; l <= 16; l++) {
        i = bits[l - 1];
        while (i--) {
            info->huffmanTabs[tab_index].sizeTab[p++] = (s8) l;
        }
    }

    info->huffmanTabs[tab_index].sizeTab[p] = 0;
    info->huffmanTabs[tab_index].numCodes = p;
    return 0;
}

static u8 __THPHuffGenerateCodeTable(THPFileInfo* info, u8 tab_index)
{
    s32 si;
    u32 code;
    s32 p;

    p = 0;
    si = info->huffmanTabs[tab_index].sizeTab[0];
    while (info->huffmanTabs[tab_index].sizeTab[p]) {
        while (info->huffmanTabs[tab_index].sizeTab[p] == si) {
            p++;
        }
        si++;
    }

    info->huffmanTabs[tab_index].codeTab = (u32*) info->scratch;
    info->scratch += p * sizeof(u32);

    p = 0;
    code = 0;
    si = info->huffmanTabs[tab_index].sizeTab[0];
    while (info->huffmanTabs[tab_index].sizeTab[p]) {
        while (info->huffmanTabs[tab_index].sizeTab[p] == si) {
            info->huffmanTabs[tab_index].codeTab[p++] = code;
            code++;
        }

        code <<= 1;
        si++;
    }

    return 0;
}

static int __THPHuffGenerateDecoderTables(THPFileInfo* info, u8 tabIndex)
{
    s32 p, l;
    THPHuffmanTab* h;

    p = 0;
    h = &info->huffmanTabs[tabIndex];
    for (l = 1; l <= 16; l++) {
        if (h->bits[l - 1]) {
            h->valPtr[l] = p - h->codeTab[p];
            p += h->bits[l - 1];
            h->maxCode[l] = h->codeTab[p - 1];
        } else {
            h->maxCode[l] = -1;
            h->valPtr[l] = -1;
        }
    }

    h->maxCode[17] = 0xfffffL;

    return 0;
}

u8 THPDec_803310CC(THPFileInfo* info)
{
    u32 i;
    s32 j;

    info->MCUsPerRow =
        (u16) THPROUNDUP(info->xPixelSize, info->samplingHMax * 8);
    info->x8D0 = (u16) THPROUNDUP(info->yPixelSize, info->samplingVMax * 8);
    info->x8CE = 0;

    for (i = 0; i < info->nComponents; i++) {
        THPComponent* c = &info->components[i];

        c->x28 = THPROUNDUP(info->xPixelSize * c->samplingH,
                            info->samplingHMax * 8);
        c->x24 = THPROUNDUP(info->yPixelSize * c->samplingV,
                            info->samplingVMax * 8);
        c->x14 = c->samplingH;
        c->x18 = c->samplingV;
        c->x1C = c->x14 * c->x18;
        c->x20 = c->x14 * 8;

        j = c->x1C;
        if (info->x8CE + c->x1C > 0x10) {
            return 0x11;
        }

        while (j-- > 0) {
            info->x8BC[info->x8CE++] = i;
        }

        if (info->x8CE > 6) {
            OSReport("THP does not support anything other than 4:2:0!\n");
            return 0;
        }

        c->predDC = 0;
    }

    return 0;
}

static u8 __THPRestartDefinition(THPFileInfo* info)
{
    info->RST = TRUE;
    info->file += 2;
    info->nMCU = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    info->currMCU = info->nMCU;
    return 0;
}

struct THPLCWork {
    u8* offsets512[2][5];
    u8* offsets672[2][9];
    u8* work512[3];
};

struct THPLCSizeEntry {
    u32 id;
    u32 size;
};

struct THPInitWork {
    struct THPLCWork cache;
    u8* work672[3];
};

static struct THPLCSizeEntry __THPLCSizeTableA[5] = {
    { 0, 0x1000 }, { 1, 0x400 }, { 2, 0x400 }, { 3, 0x400 }, { 4, 0x400 },
};

static struct THPLCSizeEntry __THPLCSizeTableB[9] = {
    { 0, 0x1000 }, { 1, 0x200 }, { 2, 0x200 }, { 3, 0x200 }, { 4, 0x200 },
    { 5, 0x200 },  { 6, 0x200 }, { 7, 0x200 }, { 8, 0x200 },
};

static __declspec(align(32)) u8 Melee360THPCache[0x4000];
static struct THPInitWork Melee360THPWork;

void THPInit(void)
{
    u8* base;
    int i;
    int j;
    struct THPInitWork* work = &Melee360THPWork;

    /* Xenon CPU decoder workspace uses native RAM, not the Gekko LC address. */

    base = Melee360THPCache;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 5; i++) {
            work->cache.offsets512[j][i] = base;
            base += __THPLCSizeTableA[i].size;
        }
    }

    base = Melee360THPCache;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 9; i++) {
            work->cache.offsets672[j][i] = base;
            base += __THPLCSizeTableB[i].size;
        }
    }

    base = Melee360THPCache;
    work->cache.work512[0] = base;
    base += 0x2000;
    work->cache.work512[1] = base;
    base += 0x800;
    work->cache.work512[2] = base;

    base = Melee360THPCache;
    work->work672[0] = base;
    base += 0x2800;
    work->work672[1] = base;
    base += 0xA00;
    work->work672[2] = base;

    /* No paired-single/GQR instructions in this native CPU header path. */
}


int Melee360THPWorkLayoutProbe(void){u8* p=Melee360THPCache;int j,i;THPInit();
 for(j=0;j<2;++j){for(i=0;i<5;++i){if(Melee360THPWork.cache.offsets512[j][i]!=p)return 0;p+=i?0x400:0x1000;}}
 if(p!=Melee360THPCache+0x4000)return 0;p=Melee360THPCache;
 for(j=0;j<2;++j){for(i=0;i<9;++i){if(Melee360THPWork.cache.offsets672[j][i]!=p)return 0;p+=i?0x200:0x1000;}}
 if(p!=Melee360THPCache+0x4000||Melee360THPWork.cache.work512[1]!=Melee360THPCache+0x2000||Melee360THPWork.cache.work512[2]!=Melee360THPCache+0x2800||Melee360THPWork.work672[1]!=Melee360THPCache+0x2800||Melee360THPWork.work672[2]!=Melee360THPCache+0x3200)return 0;
 Melee360THPWork.work672[2][0x9ff]=0x57;THPInit();return Melee360THPCache[0x3bff]==0x57;
}


typedef char Melee360THPInfoLayout[(sizeof(THPFileInfo)==0x908)?1:-1];
