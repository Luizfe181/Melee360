/* Original standalone logic subset; bodies unchanged; names isolated from full-runtime linkage. */
/* mp/mplib.c SHA256 efdcd54279ce63fdc698ee1624f8a28834bb6829a0d534aaa725196026cfb44c */
#define mpLineIntersection M360_mpLineIntersection
#define mpLineIntersectionH M360_mpLineIntersectionH
#define mpLineIntersectionV M360_mpLineIntersectionV
bool mpLineIntersection(float a0x, float a0y, float a1x, float a1y, float b0x,
                        float b0y, float b1x, float b1y, float* int_x,
                        float* int_y)
{
    bool b1_below_a = false;
    bool b2_above_a = false;

    // b entirely left/right of a
    if (a0x <= a1x) {
        if ((b0x < a0x && b1x < a0x) || (a1x < b0x && a1x < b1x)) {
            return false;
        }
    } else {
        if ((b0x < a1x && b1x < a1x) || (a0x < b0x && a0x < b1x)) {
            return false;
        }
    }

    // b entirely above/below a
    if (a0y <= a1y) {
        if ((b0y < a0y && b1y < a0y) || (a1y < b0y && a1y < b1y)) {
            return false;
        }
    } else {
        if ((b0y < a1y && b1y < a1y) || (a0y < b0y && a0y < b1y)) {
            return false;
        }
    }

    {
        double ah = a1y - a0y;
        double d0x = b0x - a0x;
        double aw = a1x - a0x;
        double d0y = b0y - a0y;
        double hs_b0_a = (aw * d0y) - (ah * d0x);
        double d1y;
        double d1x;
        double det;
        double hs_b1_a;
        double bh;
        double bw;

        if (hs_b0_a < 0.0) {
            if (hs_b0_a < -0.1) {
                return false;
            }
            b1_below_a = true;
        }

        d1x = b1x - a1x;
        d1y = b1y - a1y;

        hs_b1_a = (aw * d1y) - (ah * d1x);
        if (hs_b1_a > 0.0) {
            if (hs_b1_a > 0.1) {
                return false;
            }
            b2_above_a = true;
        }

        // check if a and b are colinear
        if (hs_b0_a == 0.0 && hs_b1_a == 0.0) {
            return false;
        }

        det = (d0x * d1y) - (d0y * d1x);
        if (det < hs_b0_a) {
            if (det < hs_b1_a) {
                return false;
            }
        } else if (det > hs_b0_a) {
            if (det > hs_b1_a) {
                return false;
            }
        }

        bw = b1x - b0x;
        bh = b1y - b0y;
        if (!((bw == 0.0 && bh == 0.0) || (b1_below_a && b2_above_a) ||
              (hs_b0_a >= 0.0 && b2_above_a)))
        {
            double area = (bw * ah) - (bh * aw);

            if (ABS(area) > 0.0001F) {
                double t =
                    ((bw * d0y) - (bh * d0x)) / area; // barycentric weight
                if (t > 0.0) {
                    if (t < 1.0) {
                        *int_x = (aw * t) + a0x;
                        *int_y = (ah * t) + a0y;
                    } else {
                        *int_x = a1x;
                        *int_y = a1y;
                    }
                } else {
                    *int_x = a0x;
                    *int_y = a0y;
                }

                goto tlabel;
            }
        }
        return false;
    tlabel:
        return true;
    }
}
bool mpLineIntersectionH(float* int_x, float* int_y, float a0x, float a0y,
                         float a1x, float b0x, float b0y, float b1x, float b1y)
{
    float max_ax;
    float min_ax;
    double dbx;
    double dby;
    double new_x;
    double dx;

    if (a0x < a1x) {
        if ((b0x < a0x && b1x < a0x) || (a1x < b0x && a1x < b1x)) {
            return false;
        }
        if (b0y - a0y < -0.0001 || b1y - a0y > 0.0001) {
            return false;
        }
        min_ax = a0x;
        max_ax = a1x;
    } else {
        if ((b0x < a1x && b1x < a1x) || (a0x < b0x && a0x < b1x)) {
            return false;
        }
        if (b1y - a0y < -0.0001 || b0y - a0y > 0.0001) {
            return false;
        }
        min_ax = a1x;
        max_ax = a0x;
    }
    dby = b1y - b0y;
    dbx = b1x - b0x;
    if (ABS(dby) < 0.0001) {
        return false;
    }
    new_x = dbx / dby * (a0y - b0y) + b0x;
    dx = new_x - min_ax;
    if (dx < 0.0) {
        if (dx < -0.1) {
            return false;
        }
        new_x = min_ax;
    }
    if (new_x - max_ax > 0.0) {
        if (new_x - max_ax > 0.1) {
            return false;
        }
        new_x = max_ax;
    }
    *int_x = new_x;
    *int_y = a0y;
    return true;
}
bool mpLineIntersectionV(float* int_x, float* int_y, float a0x, float a0y,
                         float a1y, float b0x, float b0y, float b1x, float b1y)
{
    float min_ay;
    float max_ay;
    double dbx;
    double dby;
    double new_y;
    double dy;

    if (a0y < a1y) {
        if ((b0y < a0y && b1y < a0y) || (a1y < b0y && a1y < b1y)) {
            return false;
        }
        if (b1x - a0x < -0.0001 || b0x - a0x > 0.0001) {
            return false;
        }
        min_ay = a0y;
        max_ay = a1y;
    } else {
        if ((b0y < a1y && b1y < a1y) || (a0y < b0y && a0y < b1y)) {
            return false;
        }
        if (b0x - a0x < -0.0001 || b1x - a0x > 0.0001) {
            return false;
        }
        min_ay = a1y;
        max_ay = a0y;
    }
    dby = b1y - b0y;
    dbx = b1x - b0x;
    if (ABS(dbx) < 0.0001) {
        return false;
    }
    new_y = (dby / dbx * (a0x - b0x)) + b0y;
    dy = new_y - min_ay;
    if (dy < 0.0) {
        if (dy < -0.1) {
            return false;
        }
        new_y = min_ay;
    }
    dy = new_y - max_ay;
    if (dy > 0.0) {
        if (dy > 0.1) {
            return false;
        }
        new_y = max_ay;
    }
    *int_x = a0x;
    *int_y = new_y;
    return true;
}
/* ft/ftcommon.c SHA256 3170236097c1ba15a264612e4a4628a5fedff101881e8f5936123f8e94eb8c6d */
#define ftCommon_CalcSelfAccel_Deaccel M360_ftCommon_CalcSelfAccel_Deaccel
#define ftCommon_CalcSelfAccel_AccelToVelClampedFrom M360_ftCommon_CalcSelfAccel_AccelToVelClampedFrom
#define ftCommon_CalcSelfAccel_AccelToVelClamped M360_ftCommon_CalcSelfAccel_AccelToVelClamped
#define ftCommon_CalcSelfAccel_DriftFrom M360_ftCommon_CalcSelfAccel_DriftFrom
#define ftCommon_CalcSelfAccel_AccelToVel M360_ftCommon_CalcSelfAccel_AccelToVel
#define ftCommon_CalcSelfAccel_DriftSimple M360_ftCommon_CalcSelfAccel_DriftSimple
#define ftCommon_CalcSelfAccel_DriftSimple_NoFriction M360_ftCommon_CalcSelfAccel_DriftSimple_NoFriction
#define ftCommon_ClampSelfVelX M360_ftCommon_ClampSelfVelX
#define ftCommon_ClampAirDrift M360_ftCommon_ClampAirDrift
#define ftCommon_Fall M360_ftCommon_Fall
#define ftCommon_FallBasic M360_ftCommon_FallBasic
#define ftCommon_FallFast M360_ftCommon_FallFast
#define ftCommon_ClampFallSpeed M360_ftCommon_ClampFallSpeed
#define ftCommon_Ascend M360_ftCommon_Ascend
#define ftCommon_UseAllJumps M360_ftCommon_UseAllJumps
#define ftCommon_UnlockECB M360_ftCommon_UnlockECB
void ftCommon_CalcSelfAccel_Deaccel(Fighter* fp, float friction)
{
    if (ABS(friction) >= ABS(fp->self_vel.x)) {
        friction = -fp->self_vel.x;
    } else if (fp->self_vel.x > 0) {
        friction = -friction;
    }
    fp->x74_self_accel.x = friction;
}
void ftCommon_CalcSelfAccel_AccelToVelClampedFrom(Fighter* fp, float vel,
                                                  float accel,
                                                  float target_vel,
                                                  float friction)
{
    if (!target_vel) {
        ftCommon_CalcSelfAccel_Deaccel(fp, friction);
        return;
    }

    if (!(vel * accel < 0.0F)) {
        if (accel > 0) {
            if (vel + accel > target_vel) {
                accel = -friction;
                if (vel + accel < target_vel) {
                    accel = target_vel - vel;
                }
                if (vel + accel > fp->co_attrs.air_max_horizontal_velocity) {
                    accel = fp->co_attrs.air_max_horizontal_velocity - vel;
                }
            }
        } else if (vel + accel < target_vel) {
            accel = friction;
            if (vel + accel > target_vel) {
                accel = target_vel - vel;
            }
            if (vel + accel < -fp->co_attrs.air_max_horizontal_velocity) {
                accel = -fp->co_attrs.air_max_horizontal_velocity - vel;
            }
        }
    }
    fp->x74_self_accel.x = accel;
}
void ftCommon_CalcSelfAccel_AccelToVelClamped(Fighter* fp, float accel,
                                              float target_vel, float friction)
{
    ftCommon_CalcSelfAccel_AccelToVelClampedFrom(fp, fp->self_vel.x, accel,
                                                 target_vel, friction);
}
void ftCommon_CalcSelfAccel_DriftFrom(Fighter* fp, float vel)
{
    float accel_scaling;
    float accel_flat;
    float lsx = fp->input.lstick[0].x;
    ftCo_DatAttrs* attrs = &fp->co_attrs;
    accel_scaling = lsx * attrs->air_drift_stick_mul;

    if (lsx > 0) {
        accel_flat = +attrs->aerial_drift_base;
    } else {
        accel_flat = -attrs->aerial_drift_base;
    }
    ftCommon_CalcSelfAccel_AccelToVelClampedFrom(
        fp, vel, accel_scaling + accel_flat, lsx * attrs->air_drift_max,
        attrs->aerial_friction);
}
void ftCommon_CalcSelfAccel_AccelToVel(Fighter* fp, float accel,
                                       float target_vel, float unused)
{
    if (!target_vel) {
        accel = -fp->self_vel.x;
    } else if (!(fp->self_vel.x * accel < 0)) {
        if (accel > 0) {
            if (fp->self_vel.x + accel > target_vel) {
                accel = target_vel - fp->self_vel.x;
            }
        } else {
            if (fp->self_vel.x + accel < target_vel) {
                accel = target_vel - fp->self_vel.x;
            }
        }
    }
    fp->x74_self_accel.x = accel;
}
void ftCommon_CalcSelfAccel_DriftSimple(Fighter* fp, float threshold,
                                        float accel_max, float target_max)
{
    float accel, target;

    if (ABS(fp->input.lstick[0].x) >= threshold) {
        accel = fp->input.lstick[0].x * accel_max;
        target = fp->input.lstick[0].x * target_max;
    } else {
        target = 0;
        accel = 0;
    }
    ftCommon_CalcSelfAccel_AccelToVelClamped(fp, accel, target,
                                             fp->co_attrs.aerial_friction);
}
void ftCommon_CalcSelfAccel_DriftSimple_NoFriction(Fighter* fp,
                                                   float threshold,
                                                   float accel_max,
                                                   float target_max)
{
    float accel;
    float target_vel;

    if (ABS(fp->input.lstick[0].x) >= threshold) {
        accel = fp->input.lstick[0].x * accel_max;
        target_vel = fp->input.lstick[0].x * target_max;
    } else {
        target_vel = 0;
        accel = 0;
    }

    ftCommon_CalcSelfAccel_AccelToVel(fp, accel, target_vel, 0.0F);
}
void ftCommon_ClampSelfVelX(Fighter* fp, float max)
{
    float vel = fp->self_vel.x;
    if (vel < -max) {
        fp->self_vel.x = -max;
    } else if (vel > max) {
        fp->self_vel.x = +max;
    }
}
void ftCommon_ClampAirDrift(Fighter* fp)
{
    ftCommon_ClampSelfVelX(fp, fp->co_attrs.air_drift_max);
}
void ftCommon_Fall(Fighter* fp, float gravity, float terminal_vel)
{
    fp->self_vel.y -= gravity;
    if (fp->self_vel.y < -terminal_vel) {
        fp->self_vel.y = -terminal_vel;
    }
}
void ftCommon_FallBasic(Fighter* fp)
{
    ftCommon_Fall(fp, fp->co_attrs.gravity, fp->co_attrs.terminal_velocity);
}
void ftCommon_FallFast(Fighter* fp)
{
    fp->self_vel.y = -fp->co_attrs.fast_fall_velocity;
}
void ftCommon_ClampFallSpeed(Fighter* fp, float val)
{
    if (fp->self_vel.y > val) {
        fp->self_vel.y = val;
    }
}
void ftCommon_Ascend(Fighter* fp, float accel, float max)
{
    fp->self_vel.y += accel;
    if (fp->self_vel.y > max) {
        fp->self_vel.y = max;
    }
}
void ftCommon_UseAllJumps(Fighter* fp)
{
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
}
void ftCommon_UnlockECB(Fighter* fp)
{
    fp->ecb_lock = 0;
    fp->coll_data.x130_flags &= ~CollData_X130_Locked;
}
