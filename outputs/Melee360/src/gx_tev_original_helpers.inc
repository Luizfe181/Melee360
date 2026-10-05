/* Original SDK convenience functions; shader-backed dependencies. */

#define CHECK_GXBEGIN(line,name) require(!__GXinBegin)

#define ASSERTMSGLINE(line,condition,message) do { if(!(condition)) __assert(__FILE__,line,message); } while(0)

void GXSetTevIndWarp(GXTevStageID tev_stage, GXIndTexStageID ind_stage,
                     u8 signed_offset, u8 replace_mode,
                     GXIndTexMtxID matrix_sel)
{
    GXIndTexWrap wrap = (replace_mode != 0) ? GX_ITW_0 : GX_ITW_OFF;

    CHECK_GXBEGIN(0x16E, "GXSetTevIndWarp");
    GXSetTevIndirect(tev_stage, ind_stage, GX_ITF_8,
                     (signed_offset != 0) ? GX_ITB_STU : GX_ITB_NONE,
                     matrix_sel, wrap, wrap, 0U, 0, GX_ITBA_OFF);
}

void GXSetTevIndTile(GXTevStageID tev_stage, GXIndTexStageID ind_stage,
                     u16 tilesize_s, u16 tilesize_t, u16 tilespacing_s,
                     u16 tilespacing_t, GXIndTexFormat format,
                     GXIndTexMtxID matrix_sel, GXIndTexBiasSel bias_sel,
                     GXIndTexAlphaSel alpha_sel)
{
    GXIndTexWrap wrap_s;
    GXIndTexWrap wrap_t;
    f32 mtx[2][3];

    CHECK_GXBEGIN(0x190, "GXSetTevIndTile");
    ASSERTMSGLINE(0x191, tev_stage < 16,
                  "GXSetTevIndTile: Invalid tev stage id");
    ASSERTMSGLINE(0x192, ind_stage < 4,
                  "GXSetTevIndTile: Invalid indirect stage id");
    switch (tilesize_s) {
    case 256:
        wrap_s = GX_ITW_256;
        break;
    case 128:
        wrap_s = GX_ITW_128;
        break;
    case 64:
        wrap_s = GX_ITW_64;
        break;
    case 32:
        wrap_s = GX_ITW_32;
        break;
    case 16:
        wrap_s = GX_ITW_16;
        break;
    default:
        ASSERTMSGLINE(0x19B, 0,
                      "GXSetTevIndTile: Invalid tilesize for S coordinate");
        wrap_s = GX_ITW_OFF;
        break;
    }
    switch (tilesize_t) {
    case 256:
        wrap_t = GX_ITW_256;
        break;
    case 128:
        wrap_t = GX_ITW_128;
        break;
    case 64:
        wrap_t = GX_ITW_64;
        break;
    case 32:
        wrap_t = GX_ITW_32;
        break;
    case 16:
        wrap_t = GX_ITW_16;
        break;
    default:
        ASSERTMSGLINE(0x1A7, 0,
                      "GXSetTevIndTile: Invalid tilesize for T coordinate");
        wrap_t = GX_ITW_OFF;
        break;
    }
    mtx[0][0] = tilespacing_s / 1024.0f;
    mtx[0][1] = mtx[0][2] = 0.0f;
    mtx[1][1] = tilespacing_t / 1024.0f;
    mtx[1][0] = mtx[1][2] = 0.0f;
    GXSetIndTexMtx(matrix_sel, mtx, 0xA);
    GXSetTevIndirect(tev_stage, ind_stage, format, bias_sel, matrix_sel,
                     wrap_s, wrap_t, 0U, 1, alpha_sel);
}

void GXSetTevIndBumpST(GXTevStageID tev_stage, GXIndTexStageID ind_stage,
                       GXIndTexMtxID matrix_sel)
{
    GXIndTexMtxID sm;
    GXIndTexMtxID tm;

    CHECK_GXBEGIN(0x1CF, "GXSetTevIndBumpST");
    switch (matrix_sel) {
    case GX_ITM_0:
        sm = GX_ITM_S0;
        tm = GX_ITM_T0;
        break;
    case GX_ITM_1:
        sm = GX_ITM_S1;
        tm = GX_ITM_T1;
        break;
    case GX_ITM_2:
        sm = GX_ITM_S2;
        tm = GX_ITM_T2;
        break;
    default:
        ASSERTMSGLINE(0x1E0, 0, "GXSetTevIndBumpST: Invalid matrix selection");
        break;
    }
    GXSetTevIndirect(tev_stage, ind_stage, GX_ITF_8, GX_ITB_ST, sm, GX_ITW_0,
                     GX_ITW_0, 0U, 0, GX_ITBA_OFF);
    GXSetTevIndirect((GXTevStageID)(tev_stage + 1), ind_stage, GX_ITF_8, GX_ITB_ST, tm,
                     GX_ITW_0, GX_ITW_0, 1U, 0, GX_ITBA_OFF);
    GXSetTevIndirect((GXTevStageID)(tev_stage + 2), ind_stage, GX_ITF_8, GX_ITB_NONE,
                     GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, 1U, 0, GX_ITBA_OFF);
}

void GXSetTevIndBumpXYZ(GXTevStageID tev_stage, GXIndTexStageID ind_stage,
                        GXIndTexMtxID matrix_sel)
{
    CHECK_GXBEGIN(0x214, "GXSetTevIndBumpXYZ");
    GXSetTevIndirect(tev_stage, ind_stage, GX_ITF_8, GX_ITB_STU, matrix_sel,
                     GX_ITW_OFF, GX_ITW_OFF, 0U, 0, GX_ITBA_OFF);
}

void GXSetTevIndRepeat(GXTevStageID tev_stage)
{
    CHECK_GXBEGIN(0x231, "GXSetTevIndRepeat");
    GXSetTevIndirect(tev_stage, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE,
                     GX_ITM_OFF, GX_ITW_0, GX_ITW_0, 1U, 0, GX_ITBA_OFF);
}

#undef CHECK_GXBEGIN

#undef ASSERTMSGLINE
