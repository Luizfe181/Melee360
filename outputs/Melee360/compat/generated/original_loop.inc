/* Unchanged mn_8022ED6C; source SHA256 C44C86FFE8FC9B30CD8774E39107A0F8DC731D50AF232340480193301AA74534 */
float mn_8022ED6C(HSD_JObj* jobj, AnimLoopSettings* anim_loop)
{
    float end_frame;
    float cur_frame;

    cur_frame = mn_8022F298(jobj);
    if (!(anim_loop->start_frame <= cur_frame &&
          cur_frame <= anim_loop->end_frame))
    {
        HSD_JObjReqAnimAll(jobj, *(volatile f32*) &anim_loop->start_frame);
    }
    if (anim_loop->loop_frame == -0.1f) {
        cur_frame = mn_8022F298(jobj);
        end_frame = anim_loop->end_frame;
        if (cur_frame < end_frame) {
            HSD_JObjAnimAll(jobj);
            cur_frame = mn_8022F298(jobj);
            end_frame = anim_loop->end_frame;
            if (cur_frame > end_frame) {
                cur_frame = end_frame;
                HSD_JObjReqAnimAll(jobj, cur_frame);
                HSD_JObjAnimAll(jobj);
            }
        }
    } else {
        HSD_JObjAnimAll(jobj);
        cur_frame = mn_8022F298(jobj);
        end_frame = anim_loop->end_frame;
        if (cur_frame >= end_frame) {
            cur_frame = anim_loop->loop_frame + (cur_frame - end_frame);
            HSD_JObjReqAnimAll(jobj, cur_frame);
            HSD_JObjAnimAll(jobj);
        }
    }
    return cur_frame;
}