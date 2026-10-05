/* Generated original CSS excerpts, not the complete CursorThink/scene. */

#define ICONROWHT_TOP_TOP 20.0F

#define ICONROWHT_MID_TOP 13.0F

#define ICONROWHT_BTM_TOP 6.0F

#define ICONROWHT_BTM_BTM (-1.0F)

#define ICONROWY_TOP 20.2F

#define ICONROWY_BTM 5.8F

#define ICONBNDS_COL0_L (-30.0F)

#define ICONBNDS_COL1_L (-24.4F)

#define ICONBNDS_COL2_L (-17.4F)

#define ICONBNDS_COL3_L (-10.4F)

#define ICONBNDS_COL4_L (-3.4F)

#define ICONBNDS_COL5_L 3.6F

#define ICONBNDS_COL6_L 10.6F

#define ICONBNDS_COL7_L 17.6F

#define ICONBNDS_COL8_L 24.4F

#define ICONBNDS_COL8_R 30.2F

struct CSSCursorData {
    /* 0x00 */ HSD_GObj* gobj;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
    /* 0x07 */ u8 x7;
    /* 0x08 */ u16 x8;
    /* 0x0A */ u16 xA;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
};

static CSSIcon icons[25 + 1] = {
    // -------- Icons Top Row --------

    { // Dr. Mario -                      0x803F0B24
      ICONHUD_DRMARIO, CKind_DrMario, ICONSTATE_UNLOCKED, 0x00,
      ICONJOINT_DRMARIO, ICONJOINT_DRMARIO, 0x000000C5, ICONBNDS_COL0_L,
      ICONBNDS_COL1_L, ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Mario -                          0x803F0B40
      ICONHUD_MARIO, CKind_Mario, ICONSTATE_TEMP, 0x00, ICONJOINT_MARIO,
      ICONJOINT_MARIO, 0x000000CD, ICONBNDS_COL1_L, ICONBNDS_COL2_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Luigi -                          0x803F0B5C
      ICONHUD_LUIGI, CKind_Luigi, ICONSTATE_TEMP, 0x00, ICONJOINT_LUIGI,
      ICONJOINT_LUIGI, 0x000000CC, ICONBNDS_COL2_L, ICONBNDS_COL3_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Bowser -                         0x803F0B78
      ICONHUD_KOOPA, CKind_Koopa, ICONSTATE_TEMP, 0x00, ICONJOINT_KOOPA,
      ICONJOINT_KOOPA, 0x000000CA, ICONBNDS_COL3_L, ICONBNDS_COL4_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Peach -                          0x803F0B94
      ICONHUD_PEACH, CKind_Peach, ICONSTATE_TEMP, 0x00, ICONJOINT_PEACH,
      ICONJOINT_PEACH, 0x000000D1, ICONBNDS_COL4_L, ICONBNDS_COL5_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Yoshi -                          0x803F0BB0
      ICONHUD_YOSHI, CKind_Yoshi, ICONSTATE_TEMP, 0x00, ICONJOINT_YOSHI,
      ICONJOINT_YOSHI, 0x000000D7, ICONBNDS_COL5_L, ICONBNDS_COL6_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // DK -                             0x803F0BCC
      ICONHUD_DONKEY, CKind_Donkey, ICONSTATE_TEMP, 0x00, ICONJOINT_DONKEY,
      ICONJOINT_DONKEY, 0x000000C4, ICONBNDS_COL6_L, ICONBNDS_COL7_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Captain Falcon -                 0x803F0BE8
      ICONHUD_CAPTAIN, CKind_Captain, ICONSTATE_TEMP, 0x00, ICONJOINT_CAPTAIN,
      ICONJOINT_CAPTAIN, 0x000000C2, ICONBNDS_COL7_L, ICONBNDS_COL8_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Ganondorf -                      0x803F0C04
      ICONHUD_GANON, CKind_Ganon, ICONSTATE_UNLOCKED, 0x00, ICONJOINT_GANON,
      ICONJOINT_GANON, 0x000000D9, ICONBNDS_COL8_L, ICONBNDS_COL8_R,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },

    // -------- Icons Middle Row --------

    { // Falco -                          0x803F0C20
      ICONHUD_FALCO, CKind_Falco, ICONSTATE_UNLOCKED, 0x00, ICONJOINT_FALCO,
      ICONJOINT_FALCO, 0x000000C6, ICONBNDS_COL0_L, ICONBNDS_COL1_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Fox -                            0x803F0C3C
      ICONHUD_FOX, CKind_Fox, ICONSTATE_TEMP, 0x00, ICONJOINT_FOX,
      ICONJOINT_FOX, 0x000000C7, ICONBNDS_COL1_L, ICONBNDS_COL2_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Ness -                           0x803F0C58
      ICONHUD_NESS, CKind_Ness, ICONSTATE_TEMP, 0x00, ICONJOINT_NESS,
      ICONJOINT_NESS, 0x000000D0, ICONBNDS_COL2_L, ICONBNDS_COL3_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // ICs -                            0x803F0C74
      ICONHUD_POPONANA, CKind_PopoNana, ICONSTATE_TEMP, 0x00,
      ICONJOINT_POPONANA, ICONJOINT_POPONANA, 0x000000C8, ICONBNDS_COL3_L,
      ICONBNDS_COL4_L, ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Kirby -                          0x803F0C90
      ICONHUD_KIRBY, CKind_Kirby, ICONSTATE_TEMP, 0x00, ICONJOINT_KIRBY,
      ICONJOINT_KIRBY, 0x000000C9, ICONBNDS_COL4_L, ICONBNDS_COL5_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Samus -                          0x803F0CAC
      ICONHUD_SAMUS, CKind_Samus, ICONSTATE_TEMP, 0x00, ICONJOINT_SAMUS,
      ICONJOINT_SAMUS, 0x000000D5, ICONBNDS_COL5_L, ICONBNDS_COL6_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Zelda -                          0x803F0CC8
      ICONHUD_ZELDA, CKind_Zelda, ICONSTATE_TEMP, 0x00, ICONJOINT_ZELDA,
      ICONJOINT_ZELDA, 0x000000D6, ICONBNDS_COL6_L, ICONBNDS_COL7_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Link -                           0x803F0CE4
      ICONHUD_LINK, CKind_Link, ICONSTATE_TEMP, 0x00, ICONJOINT_LINK,
      ICONJOINT_LINK, 0x000000CB, ICONBNDS_COL7_L, ICONBNDS_COL8_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Young Link -                     0x803F0D00
      ICONHUD_CLINK, CKind_CLink, ICONSTATE_UNLOCKED, 0x00, ICONJOINT_CLINK,
      ICONJOINT_CLINK, 0x000000C3, ICONBNDS_COL8_L, ICONBNDS_COL8_R,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },

    // -------- Icons Bottom Row --------

    { // Pichu -                          0x803F0D1C
      ICONHUD_PICHU, CKind_Pichu, ICONSTATE_UNLOCKED, 0x00, ICONJOINT_PICHU,
      ICONJOINT_PICHU, 0x000000D2, -23.4, ICONBNDS_COL2_L, ICONROWHT_BTM_TOP,
      ICONROWHT_BTM_BTM },
    { // Pikachu -                        0x803F0D38
      ICONHUD_PIKACHU, CKind_Pikachu, ICONSTATE_TEMP, 0x00, ICONJOINT_PIKACHU,
      ICONJOINT_PIKACHU, 0x000000D3, ICONBNDS_COL2_L, ICONBNDS_COL3_L,
      ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
    { // Jigglypuff -                     0x803F0D54
      ICONHUD_PURIN, CKind_Purin, ICONSTATE_TEMP, 0x00, ICONJOINT_PURIN,
      ICONJOINT_PURIN, 0x000000D4, ICONBNDS_COL3_L, ICONBNDS_COL4_L,
      ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
    { // Mewtwo -                         0x803F0D70
      ICONHUD_MEWTWO, CKind_Mewtwo, ICONSTATE_TEMP, 0x00, ICONJOINT_MEWTWO,
      ICONJOINT_MEWTWO, 0x000000CF, ICONBNDS_COL4_L, ICONBNDS_COL5_L,
      ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
    { // Mr. Game & Watch -               0x803F0D8C
      ICONHUD_GAMEWATCH, CKind_GameWatch, ICONSTATE_TEMP, 0x00,
      ICONJOINT_GAMEWATCH, ICONJOINT_GAMEWATCH, 0x000000D8, ICONBNDS_COL5_L,
      ICONBNDS_COL6_L, ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
    { // Marth -                          0x803F0DA8
      ICONHUD_MARS, CKind_Mars, ICONSTATE_TEMP, 0x00, ICONJOINT_MARS,
      ICONJOINT_MARS, 0x000000CE, ICONBNDS_COL6_L, ICONBNDS_COL7_L,
      ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
    { // Roy -                            0x803F0DC4
      ICONHUD_EMBLEM, CKind_Emblem, ICONSTATE_UNLOCKED, 0x00, ICONJOINT_EMBLEM,
      ICONJOINT_EMBLEM, 0x000000DA, ICONBNDS_COL7_L, 23.6, ICONROWHT_BTM_TOP,
      ICONROWHT_BTM_BTM }
};

static inline f32 loadStickValue(const s8* value)
{
    return (f32) *value;
}

static inline void getStickDelta(int port, f32* dx, f32* dy)
{
    f32 stick_x = loadStickValue(&HSD_PadCopyStatus[(u8) port].stickX);
    f32 stick_y = (f32) HSD_PadCopyStatus[(u8) port].stickY;
    f32 mag_sq = (stick_x * stick_x) + (stick_y * stick_y);
    if (mag_sq < 200.0f) {
        *dy = 0.0f;
        *dx = 0.0f;
    } else {
        f32 angle;
        f32 adj;
        adj = mag_sq - 200.0f;
        angle = atan2f(stick_x, stick_y);
        *dx = adj * sinf(angle);
        *dy = adj * cosf(angle);
    }
}

static inline s32 getIconOffset(u32 icon_idx)
{
    return icon_idx * sizeof(CSSIcon);
}

static inline s32 getPlayerForDoor(u8 door)
{
    if (mnCharSel_804D6CF5 == 1) {
        if (door != 0) {
            return mnCharSel_804D6CF1;
        }
        return mnCharSel_804D6CF0;
    }
    return door;
}

struct CSSCharModel {
    /* 0x00 */ HSD_GObj* gobj;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
    /* 0x07 */ u8 x7;
    /* 0x08 */ float x8;
    /* 0x0C */ float xC;
    /* 0x10 */ float x10;
    /* 0x14 */ float x14;
};

static void originalMove(struct CSSCursorData* cursor,f32 dx,f32 dy){
        cursor->xC = (f32) ((0.0002f * dx) + cursor->xC);
        cursor->x10 = (f32) ((0.0002f * dy) + cursor->x10);
                if (25.0f < cursor->x10) {
                    cursor->x10 = 25.0f;
                }
                if (-22.0f > cursor->x10) {
                    cursor->x10 = -22.0f;
                }
                if (26.0f < cursor->xC) {
                    cursor->xC = 26.0f;
                }
                if (-35.0f > cursor->xC) {
                    cursor->xC = -35.0f;
                }
}

static int originalHit(struct CSSCharModel* m2){int i;for(i=0;i<0x19;++i){if (m2->x8 > icons[i].bound_l &&
                                        m2->x8 < icons[i].bound_r &&
                                        m2->xC < icons[i].bound_u &&
                                        m2->xC > icons[i].bound_d &&
                                        icons[i].state >= 1)
                                    return i;}return -1;}

static void originalFollow(struct CSSCharModel* model){u8 status=model->x5;            model->x8 = 2.7f + mnCharSel_804A0BC0[status - 1]->xC;
            model->xC = -2.0f + mnCharSel_804A0BC0[model->x5 - 1]->x10;}

static void originalSmooth(struct CSSCharModel* model)    {
        f32 dx;
        f32 tx;
        f32 dy;

        dx = model->x10 - (tx = model->x8);
        dy = model->x14 - model->xC;

        if ((dx * dx + dy * dy) < 4.0f) {
            model->x10 = tx;
            model->x14 = model->xC;
        } else {
            f32 angle;
            if (dy < 0.01f && dy > -0.01f) {
                angle = (f32) (dx < 0.0f ? 1.5707963267948966
                                         : -1.5707963267948966);
            } else {
                angle = (f32) ((dy < 0.0f ? 0.0 : 3.141592653589793) +
                               atanf(dx / dy));
            }
            model->x10 = (3.0f * sinf(angle)) + model->x10;
            model->x14 = (3.0f * cosf(angle)) + model->x14;
        }
    }

static void originalStoreCharacter(int door){                                            s32 player_idx;
                                            if (mnCharSel_804D6CF5 == 1) {
                                                if ((s32) door != 0) {
                                                    player_idx =
                                                        mnCharSel_804D6CF1;
                                                } else {
                                                    player_idx =
                                                        mnCharSel_804D6CF0;
                                                }
                                            } else {
                                                player_idx = door;
                                            }
                                            mnCharSel_804D6CB0->vs.start
                                                .players[player_idx]
                                                .ckind =
                                                (s8) icons[mnCharSel_803F0DFC
                                                               .doors[door]
                                                               .sel_icon]
                                                    .char_kind;}

static void originalPlaceToken(int door,int icon_idx){        mnCharSel_804A0BD0[door]->x8 = 3.4f + icons[icon_idx].bound_l;
        mnCharSel_804A0BD0[door]->xC = -3.0f + icons[icon_idx].bound_u;}
