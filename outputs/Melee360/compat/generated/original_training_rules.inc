/* gm/gm_1601.c SHA256 c63fdaecfd605e8fd3bb779b282e4c01aa743c8b2bf95059472da5f07f36b159 */
void gm_SetupPlayerDefaults(struct PlayerInitData* player)
{
    memzero(player, sizeof(*player));
    player->ckind = ChKind_None;
    player->slot_type = Gm_PKind_NA;
    player->stocks = 0;
    player->color = 0;
    player->slot = 0;
    player->spawn_pos = -1;
    player->spawn_dir = 0;
    player->xB = 0;
    player->sub_color = 0;
    player->handicap = 9;
    player->team = 0;
    player->rumble_enabled = false;
    player->nametag = GM_NAMETAG_COUNT;
    player->xC_b1 = true;
    player->cpu_kind = 4;
    player->cpu_level = 0;
    player->damage1 = 0;
    player->hp = 0;
    player->attack_ratio = 1.0F;
    player->defense_ratio = 1.0F;
    player->model_scale = 1.0F;
}
void gm_SetupAllPlayerDefaults(struct PlayerInitData* player)
{
    ssize_t i;
    for (i = 0; i < Gm_Player_NumMax; i++) {
        gm_SetupPlayerDefaults(&player[i]);
    }
}
void gm_SetupRulesDefaults(struct StartMeleeRules* rules)
{
    memzero(rules, sizeof(*rules));
    rules->x0_3 = 4;

    rules->sd_penalty = 0;
    rules->item_freq = 2;

    rules->x20 = -1;
    rules->x28 = 0;

    rules->x3_1 = true;

    rules->x3_5 = true;
    rules->x3_4 = true;
    rules->x4_0 = true;

    rules->timer_shows_hours = false;
    rules->x2_5 = true;
    rules->x2_6 = true;

    rules->x2C = 1.0f;
    rules->x30 = 1.0f;
    rules->game_speed = 1.0f;

    rules->x4_6 = true;
    rules->x4_7 = true;
    rules->xD = 110;
    rules->xA = 0;
}
/* gm/gm_1B03.c SHA256 796cc6d8354c0800e396974ecba9ce32416582a962d1ab98ccfeac99bc4c94aa */
void gm_801B05F4(PlayerInitData* player, int slot)
{
    player->slot = slot + 1;
    if (slot == 2) {
        slot = 3;
    } else if (slot == 3) {
        slot = 2;
    }
    player->team = slot;
}
void gm_SetupHumanPlayer(PlayerInitData* player, u8 ckind, u8 color, u8 stocks,
                         u8 slot)
{
    player->slot_type = Gm_PKind_Human;
    player->ckind = ckind;
    player->color = color;
    player->stocks = stocks;
    gm_801B05F4(player, slot);
}
void gm_SetupCpuPlayer(PlayerInitData* arg0, u8 ckind, u8 color, u8 stocks,
                       u8 slot)
{
    arg0->slot_type = Gm_PKind_Cpu;
    arg0->ckind = ckind;
    arg0->color = color;
    arg0->stocks = stocks;
    gm_801B05F4(arg0, slot);
    arg0->team = 4;
}
/* gm/gm_1884.c SHA256 2050511190cff70f13c3b5dfc962f58ea1822c9738fc14a6ede2ae86361cf81c */
void gm_80189CDC(StartMeleeData* arg0)
{
    TrainingModeState* state = &lbl_80473700;
    s32 i;

    arg0->rules.match_kind = 0;
    arg0->rules.is_teams = 1;
    arg0->rules.item_freq = -1;
    arg0->rules.x20 = 0xFFFFFFFFFFFFFFFFULL;
    arg0->rules.x5_0 = 1;

    for (i = 0; i < 4; i++) {
        state->players[i] = gm_80473814.saved_players[i] = arg0->players[i];
    }

    state->mode = (s32) (arg0->players[0].slot - 1);
    state->count = 1;

    for (i = 0; 0x1B > i; i++) {
        state->char_data[i] = 0;
    }
}
