/* Generated from unchanged upstream mnmain.c; do not edit. SHA256: 1DE2252DF349E63E4508685C4D687A26D8F5AFAD7341853B8BA7848444EF838C */
static inline void decrement_selection(u8 selection_count, s32 menu_kind)
{
    do {
        if (mn_804A04F0.hovered_selection != 0) {
            mn_804A04F0.hovered_selection--;
        } else {
            mn_804A04F0.hovered_selection = selection_count - 1;
        }
    } while (mn_80229938(menu_kind, mn_804A04F0.hovered_selection) == 0);
}

static inline void increment_selection(u8 selection_count, MenuKind menu_kind)
{
    do {
        if (mn_804A04F0.hovered_selection == selection_count - 1) {
            mn_804A04F0.hovered_selection = 0;
        } else {
            mn_804A04F0.hovered_selection++;
        }
    } while (mn_80229938(menu_kind, mn_804A04F0.hovered_selection) == 0);
}

void mn_8022DB10(HSD_GObj* gp)
{
    MenuExitData* data;
    MenuKind menu_kind;
    void (*temp_r28)(HSD_GObj*);
    int selection_count;
    u16 hovered_selection;
    HSD_GObjProc* temp_r3_2;
    MenuFlow* mf = &mn_804A04F0;
    u8* prev_menu_ptr;
    u16* selection_ptr;
    u32 buttons;
    PAD_STACK(8);

    selection_count = mn_803EB6B0[MENU_KIND_MAIN].selection_count & 0xFF;
    buttons = mn_80229624(4);
    mf->buttons = buttons;
    if (buttons & MenuInput_Confirm) {
        mn_804D6BC8.cooldown = 5;
        mf->entering_menu = 1;
        sfxForward();
        prev_menu_ptr = &mf->prev_menu;
        selection_ptr = &mf->hovered_selection;
        *prev_menu_ptr = mf->cur_menu;
        switch (mf->hovered_selection) {
        case SEL_MAIN_1P:
            menu_kind = MENU_KIND_1P;
            hovered_selection = 0;
            break;
        case SEL_MAIN_VS:
            menu_kind = MENU_KIND_VS;
            hovered_selection = 0;
            break;
        case SEL_MAIN_TOY:
            menu_kind = MENU_KIND_TOY;
            hovered_selection = 0;
            break;
        case SEL_MAIN_SETTINGS:
            menu_kind = MENU_KIND_SETTINGS;
            hovered_selection = 0;
            break;
        case SEL_MAIN_DATA:
            menu_kind = MENU_KIND_DATA;
            hovered_selection = 0;
            break;
        }
        mn_804D6BC8.cooldown = 5;
        *prev_menu_ptr = mf->cur_menu;
        mf->cur_menu = menu_kind;
        *selection_ptr = hovered_selection;
        HSD_GObj_80390CD4(mn_8022B3A0(1));
        HSD_GObjFree(HSD_GObj_CurrentInvokedProcGObj);
        /// @todo casting u64 here makes it match, but i dont know why
        if ((temp_r28 = mn_803EB6B0[(u64) menu_kind].think)) {
            temp_r3_2 =
                HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), temp_r28, 0);
            temp_r3_2->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuInput_Back) {
        sfxBack();
        mf->entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        data = gm_GetCurrentSceneExitData();
        data->pending_mode = GM_TITLE;
        gm_801A4B60();
    } else if (buttons & MenuInput_Up) {
        sfxMove();
        decrement_selection(selection_count, MENU_KIND_MAIN);
    } else if (buttons & MenuInput_Down) {
        sfxMove();
        increment_selection(selection_count, MENU_KIND_MAIN);
    }
}

