/* Generated unchanged C implementations; paired-single assembly excluded. */

#define DEBUG 1

#include <dolphin/mtx.h>

#include <sysdolphin/baselib/debug.h>

#include <math.h>

#undef sinf

#undef cosf

extern float sinf(float);

extern float cosf(float);

#define MTXRotTrig C_MTXRotTrig

#define ASSERTMSGLINE(line,condition,message) HSD_ASSERTREPORT(line,condition,message)

void C_MTXIdentity(Mtx m)
{
    ASSERTMSGLINE(0xA1, m, "MtxIdentity():  NULL Mtx 'm' ");
    m[0][0] = 1;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = 1;
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;
    m[2][3] = 0;
}

void C_MTXCopy(Mtx src, Mtx dst)
{
    ASSERTMSGLINE(0xDE, src, "MTXCopy():  NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0xDF, dst, "MTXCopy():  NULL MtxPtr 'dst' ");
    if (src != dst) {
        dst[0][0] = src[0][0];
        dst[0][1] = src[0][1];
        dst[0][2] = src[0][2];
        dst[0][3] = src[0][3];
        dst[1][0] = src[1][0];
        dst[1][1] = src[1][1];
        dst[1][2] = src[1][2];
        dst[1][3] = src[1][3];
        dst[2][0] = src[2][0];
        dst[2][1] = src[2][1];
        dst[2][2] = src[2][2];
        dst[2][3] = src[2][3];
    }
}

void C_MTXConcat(Mtx a, Mtx b, Mtx ab)
{
    Mtx mTmp;
    f32(*m)[4];

    ASSERTMSGLINE(0x128, a, "MTXConcat():  NULL MtxPtr 'a'  ");
    ASSERTMSGLINE(0x129, b, "MTXConcat():  NULL MtxPtr 'b'  ");
    ASSERTMSGLINE(0x12A, ab, "MTXConcat():  NULL MtxPtr 'ab' ");

    if (ab == a || ab == b) {
        m = mTmp;
    } else {
        m = ab;
    }

    m[0][0] =
        0 + a[0][2] * b[2][0] + ((a[0][0] * b[0][0]) + (a[0][1] * b[1][0]));
    m[0][1] =
        0 + a[0][2] * b[2][1] + ((a[0][0] * b[0][1]) + (a[0][1] * b[1][1]));
    m[0][2] =
        0 + a[0][2] * b[2][2] + ((a[0][0] * b[0][2]) + (a[0][1] * b[1][2]));
    m[0][3] = a[0][3] +
              (a[0][2] * b[2][3] + (a[0][0] * b[0][3] + (a[0][1] * b[1][3])));

    m[1][0] =
        0 + a[1][2] * b[2][0] + ((a[1][0] * b[0][0]) + (a[1][1] * b[1][0]));
    m[1][1] =
        0 + a[1][2] * b[2][1] + ((a[1][0] * b[0][1]) + (a[1][1] * b[1][1]));
    m[1][2] =
        0 + a[1][2] * b[2][2] + ((a[1][0] * b[0][2]) + (a[1][1] * b[1][2]));
    m[1][3] = a[1][3] +
              (a[1][2] * b[2][3] + (a[1][0] * b[0][3] + (a[1][1] * b[1][3])));

    m[2][0] =
        0 + a[2][2] * b[2][0] + ((a[2][0] * b[0][0]) + (a[2][1] * b[1][0]));
    m[2][1] =
        0 + a[2][2] * b[2][1] + ((a[2][0] * b[0][1]) + (a[2][1] * b[1][1]));
    m[2][2] =
        0 + a[2][2] * b[2][2] + ((a[2][0] * b[0][2]) + (a[2][1] * b[1][2]));
    m[2][3] = a[2][3] +
              (a[2][2] * b[2][3] + (a[2][0] * b[0][3] + (a[2][1] * b[1][3])));

    if (m == mTmp) {
        C_MTXCopy(mTmp, ab);
    }
}

void C_MTXTranspose(Mtx src, Mtx xPose)
{
    Mtx mTmp;
    f32(*m)[4];

    ASSERTMSGLINE(0x22D, src, "MTXTranspose():  NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x22E, xPose, "MTXTranspose():  NULL MtxPtr 'xPose' ");

    if (src == xPose) {
        m = mTmp;
    } else {
        m = xPose;
    }

    m[0][0] = src[0][0];
    m[0][1] = src[1][0];
    m[0][2] = src[2][0];
    m[0][3] = 0;
    m[1][0] = src[0][1];
    m[1][1] = src[1][1];
    m[1][2] = src[2][1];
    m[1][3] = 0;
    m[2][0] = src[0][2];
    m[2][1] = src[1][2];
    m[2][2] = src[2][2];
    m[2][3] = 0;
    if (m == mTmp) {
        C_MTXCopy(mTmp, xPose);
    }
}

u32 C_MTXInverse(Mtx src, Mtx inv)
{
    Mtx mTmp;
    f32(*m)[4];
    f32 det;

    ASSERTMSGLINE(0x290, src, "MTXInverse():  NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x291, inv, "MTXInverse():  NULL MtxPtr 'inv' ");

    if (src == inv) {
        m = mTmp;
    } else {
        m = inv;
    }
    det = ((((src[2][1] * (src[0][2] * src[1][0])) +
             ((src[2][2] * (src[0][0] * src[1][1])) +
              (src[2][0] * (src[0][1] * src[1][2])))) -
            (src[0][2] * (src[2][0] * src[1][1]))) -
           (src[2][2] * (src[1][0] * src[0][1]))) -
          (src[1][2] * (src[0][0] * src[2][1]));
    if (0 == det) {
        return 0;
    }
    det = 1 / det;
    m[0][0] = (det * +((src[1][1] * src[2][2]) - (src[2][1] * src[1][2])));
    m[0][1] = (det * -((src[0][1] * src[2][2]) - (src[2][1] * src[0][2])));
    m[0][2] = (det * +((src[0][1] * src[1][2]) - (src[1][1] * src[0][2])));

    m[1][0] = (det * -((src[1][0] * src[2][2]) - (src[2][0] * src[1][2])));
    m[1][1] = (det * +((src[0][0] * src[2][2]) - (src[2][0] * src[0][2])));
    m[1][2] = (det * -((src[0][0] * src[1][2]) - (src[1][0] * src[0][2])));

    m[2][0] = (det * +((src[1][0] * src[2][1]) - (src[2][0] * src[1][1])));
    m[2][1] = (det * -((src[0][0] * src[2][1]) - (src[2][0] * src[0][1])));
    m[2][2] = (det * +((src[0][0] * src[1][1]) - (src[1][0] * src[0][1])));

    m[0][3] = ((-m[0][0] * src[0][3]) - (m[0][1] * src[1][3])) -
              (m[0][2] * src[2][3]);
    m[1][3] = ((-m[1][0] * src[0][3]) - (m[1][1] * src[1][3])) -
              (m[1][2] * src[2][3]);
    m[2][3] = ((-m[2][0] * src[0][3]) - (m[2][1] * src[1][3])) -
              (m[2][2] * src[2][3]);

    if (m == mTmp) {
        C_MTXCopy(mTmp, inv);
    }
    return 1;
}

u32 C_MTXInvXpose(Mtx src, Mtx invX)
{
    Mtx mTmp;
    f32(*m)[4];
    f32 det;

    ASSERTMSGLINE(0x380, src, "MTXInvXpose(): NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x381, invX, "MTXInvXpose(): NULL MtxPtr 'invX' ");

    if (src == invX) {
        m = mTmp;
    } else {
        m = invX;
    }
    det = ((((src[2][1] * (src[0][2] * src[1][0])) +
             ((src[2][2] * (src[0][0] * src[1][1])) +
              (src[2][0] * (src[0][1] * src[1][2])))) -
            (src[0][2] * (src[2][0] * src[1][1]))) -
           (src[2][2] * (src[1][0] * src[0][1]))) -
          (src[1][2] * (src[0][0] * src[2][1]));
    if (0 == det) {
        return 0;
    }
    det = 1 / det;
    m[0][0] = (det * +((src[1][1] * src[2][2]) - (src[2][1] * src[1][2])));
    m[0][1] = (det * -((src[1][0] * src[2][2]) - (src[2][0] * src[1][2])));
    m[0][2] = (det * +((src[1][0] * src[2][1]) - (src[2][0] * src[1][1])));

    m[1][0] = (det * -((src[0][1] * src[2][2]) - (src[2][1] * src[0][2])));
    m[1][1] = (det * +((src[0][0] * src[2][2]) - (src[2][0] * src[0][2])));
    m[1][2] = (det * -((src[0][0] * src[2][1]) - (src[2][0] * src[0][1])));

    m[2][0] = (det * +((src[0][1] * src[1][2]) - (src[1][1] * src[0][2])));
    m[2][1] = (det * -((src[0][0] * src[1][2]) - (src[1][0] * src[0][2])));
    m[2][2] = (det * +((src[0][0] * src[1][1]) - (src[1][0] * src[0][1])));

    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;

    if (m == mTmp) {
        C_MTXCopy(mTmp, invX);
    }
    return 1;
}

void C_MTXRotTrig(Mtx m, char axis, f32 sinA, f32 cosA)
{
    ASSERTMSGLINE(0x4AF, m, "MTXRotTrig():  NULL MtxPtr 'm' ");
    switch (axis) {
    case 120:
    case 88:
        m[0][0] = 1;
        m[0][1] = 0;
        m[0][2] = 0;
        m[0][3] = 0;
        m[1][0] = 0;
        m[1][1] = cosA;
        m[1][2] = -sinA;
        m[1][3] = 0;
        m[2][0] = 0;
        m[2][1] = sinA;
        m[2][2] = cosA;
        m[2][3] = 0;
        break;
    case 121:
    case 89:
        m[0][0] = cosA;
        m[0][1] = 0;
        m[0][2] = sinA;
        m[0][3] = 0;
        m[1][0] = 0;
        m[1][1] = 1;
        m[1][2] = 0;
        m[1][3] = 0;
        m[2][0] = -sinA;
        m[2][1] = 0;
        m[2][2] = cosA;
        m[2][3] = 0;
        break;
    case 122:
    case 90:
        m[0][0] = cosA;
        m[0][1] = -sinA;
        m[0][2] = 0;
        m[0][3] = 0;
        m[1][0] = sinA;
        m[1][1] = cosA;
        m[1][2] = 0;
        m[1][3] = 0;
        m[2][0] = 0;
        m[2][1] = 0;
        m[2][2] = 1;
        m[2][3] = 0;
        break;
    default:
        ASSERTMSGLINE(0x4CB, FALSE, "MTXRotTrig():  invalid 'axis' value ");
        break;
    }
}

void C_MTXRotAxisRad(Mtx m, Vec* axis, f32 rad)
{
    Vec vN;
    f32 s;
    f32 c;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    f32 xSq;
    f32 ySq;
    f32 zSq;

    ASSERTMSGLINE(0x50B, m, "MTXRotAxisRad():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x50C, axis, "MTXRotAxisRad():  NULL VecPtr 'axis' ");

    s = sinf(rad);
    c = cosf(rad);
    t = 1 - c;
    VECNormalize(axis, &vN);
    x = vN.x;
    y = vN.y;
    z = vN.z;
    xSq = (x * x);
    ySq = (y * y);
    zSq = (z * z);
    m[0][0] = (c + (t * xSq));
    m[0][1] = (y * (t * x)) - (s * z);
    m[0][2] = (z * (t * x)) + (s * y);
    m[0][3] = 0;
    m[1][0] = ((y * (t * x)) + (s * z));
    m[1][1] = (c + (t * ySq));
    m[1][2] = ((z * (t * y)) - (s * x));
    m[1][3] = 0;
    m[2][0] = ((z * (t * x)) - (s * y));
    m[2][1] = ((z * (t * y)) + (s * x));
    m[2][2] = (c + (t * zSq));
    m[2][3] = 0;
}

void C_MTXScale(Mtx m, f32 xS, f32 yS, f32 zS)
{
    ASSERTMSGLINE(0x58A, m, "MTXScale():  NULL MtxPtr 'm' ");
    m[0][0] = xS;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = yS;
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = zS;
    m[2][3] = 0;
}

void C_MTXQuat(Mtx m, QuaternionPtr q)
{
    f32 s;
    f32 xs;
    f32 ys;
    f32 zs;
    f32 wx;
    f32 wy;
    f32 wz;
    f32 xx;
    f32 xy;
    f32 xz;
    f32 yy;
    f32 yz;
    f32 zz;

    ASSERTMSGLINE(0x5C9, m, "MTXQuat():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x5CA, q, "MTXQuat():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(0x5CB, q->x || q->y || q->z || q->w,
                  "MTXQuat():  zero-value quaternion ");
    s = 2 /
        ((q->w * q->w) + ((q->z * q->z) + ((q->x * q->x) + (q->y * q->y))));
    xs = q->x * s;
    ys = q->y * s;
    zs = q->z * s;
    wx = q->w * xs;
    wy = q->w * ys;
    wz = q->w * zs;
    xx = q->x * xs;
    xy = q->x * ys;
    xz = q->x * zs;
    yy = q->y * ys;
    yz = q->y * zs;
    zz = q->z * zs;
    m[0][0] = (1 - (yy + zz));
    m[0][1] = (xy - wz);
    m[0][2] = (xz + wy);
    m[0][3] = 0;
    m[1][0] = (xy + wz);
    m[1][1] = (1 - (xx + zz));
    m[1][2] = (yz - wx);
    m[1][3] = 0;
    m[2][0] = (xz - wy);
    m[2][1] = (yz + wx);
    m[2][2] = (1 - (xx + yy));
    m[2][3] = 0;
}

void C_MTXLookAt(Mtx m, Vec* camPos, Vec* camUp, Vec* target)
{
    Vec vLook;
    Vec vRight;
    Vec vUp;

    vLook.x = camPos->x - target->x;
    vLook.y = camPos->y - target->y;
    vLook.z = camPos->z - target->z;
    VECNormalize(&vLook, &vLook);

    VECCrossProduct(camUp, &vLook, &vRight);
    VECNormalize(&vRight, &vRight);
    VECCrossProduct(&vLook, &vRight, &vUp);

    m[0][0] = vRight.x;
    m[0][1] = vRight.y;
    m[0][2] = vRight.z;
    m[0][3] = -((camPos->z * vRight.z) +
                ((camPos->x * vRight.x) + (camPos->y * vRight.y)));

    m[1][0] = vUp.x;
    m[1][1] = vUp.y;
    m[1][2] = vUp.z;
    m[1][3] =
        -((camPos->z * vUp.z) + ((camPos->x * vUp.x) + (camPos->y * vUp.y)));

    m[2][0] = vLook.x;
    m[2][1] = vLook.y;
    m[2][2] = vLook.z;
    m[2][3] = -((camPos->z * vLook.z) +
                ((camPos->x * vLook.x) + (camPos->y * vLook.y)));
}

void MTXTransApply(Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT)
{
    ASSERTMSGLINE(0x567, src, "MTXTransApply(): NULL MtxPtr 'src' ");
    ASSERTMSGLINE(
        0x568, dst,
        "MTXTransApply(): NULL MtxPtr 'src' "); //! wrong assert string

    if (src != dst) {
        dst[0][0] = src[0][0];
        dst[0][1] = src[0][1];
        dst[0][2] = src[0][2];
        dst[1][0] = src[1][0];
        dst[1][1] = src[1][1];
        dst[1][2] = src[1][2];
        dst[2][0] = src[2][0];
        dst[2][1] = src[2][1];
        dst[2][2] = src[2][2];
    }
    dst[0][3] = (src[0][3] + xT);
    dst[1][3] = (src[1][3] + yT);
    dst[2][3] = (src[2][3] + zT);
}

void MTXScaleApply(Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS)
{
    ASSERTMSGLINE(0x5A8, src, "MTXScaleApply(): NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x5A9, dst, "MTXScaleApply(): NULL MtxPtr 'dst' ");
    dst[0][0] = (src[0][0] * xS);
    dst[0][1] = (src[0][1] * xS);
    dst[0][2] = (src[0][2] * xS);
    dst[0][3] = (src[0][3] * xS);
    dst[1][0] = (src[1][0] * yS);
    dst[1][1] = (src[1][1] * yS);
    dst[1][2] = (src[1][2] * yS);
    dst[1][3] = (src[1][3] * yS);
    dst[2][0] = (src[2][0] * zS);
    dst[2][1] = (src[2][1] * zS);
    dst[2][2] = (src[2][2] * zS);
    dst[2][3] = (src[2][3] * zS);
}

void MTXRotRad(Mtx m, char axis, f32 rad)
{
    f32 sinA;
    f32 cosA;

    ASSERTMSGLINE(0x48B, m, "MTXRotRad():  NULL MtxPtr 'm' ");
    sinA = sinf(rad);
    cosA = cosf(rad);
    MTXRotTrig(m, axis, sinA, cosA);
}

void MTXLightFrustum(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 scaleS,
                     f32 scaleT, f32 transS, f32 transT)
{
    f32 tmp;

    ASSERTMSGLINE(0x6A2, m, "MTXLightFrustum():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(
        0x6A3, (t != b),
        "MTXLightFrustum():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(
        0x6A4, (l != r),
        "MTXLightFrustum():  'l' and 'r' clipping planes are equal ");

    tmp = 1 / (r - l);
    m[0][0] = (scaleS * (2 * n * tmp));
    m[0][1] = 0;
    m[0][2] = (scaleS * (tmp * (r + l))) - transS;
    m[0][3] = 0;
    tmp = 1 / (t - b);
    m[1][0] = 0;
    m[1][1] = (scaleT * (2 * n * tmp));
    m[1][2] = (scaleT * (tmp * (t + b))) - transT;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = -1;
    m[2][3] = 0;
}

void MTXLightPerspective(Mtx m, f32 fovY, f32 aspect, f32 scaleS, f32 scaleT,
                         f32 transS, f32 transT)
{
    f32 angle;
    f32 cot;

    ASSERTMSGLINE(0x6DF, m, "MTXLightPerspective():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x6E0, (fovY > 0.0) && (fovY < 180.0),
                  "MTXLightPerspective():  'fovY' out of range ");
    ASSERTMSGLINE(0x6E1, 0 != aspect,
                  "MTXLightPerspective():  'aspect' is 0 ");

    angle = (0.5f * fovY);
    angle = angle * 0.017453293f;
    cot = 1 / tanf(angle);
    m[0][0] = (scaleS * (cot / aspect));
    m[0][1] = 0;
    m[0][2] = -transS;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = (cot * scaleT);
    m[1][2] = -transT;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = -1;
    m[2][3] = 0;
}

void MTXLightOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT,
                   f32 transS, f32 transT)
{
    f32 tmp;

    ASSERTMSGLINE(0x720, m, "MTXLightOrtho():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x721, (t != b),
                  "MTXLightOrtho():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(0x722, (l != r),
                  "MTXLightOrtho():  'l' and 'r' clipping planes are equal ");
    tmp = 1 / (r - l);
    m[0][0] = (2 * tmp * scaleS);
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = (transS + (scaleS * (tmp * -(r + l))));
    tmp = 1 / (t - b);
    m[1][0] = 0;
    m[1][1] = (2 * tmp * scaleT);
    m[1][2] = 0;
    m[1][3] = (transT + (scaleT * (tmp * -(t + b))));
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 0;
    m[2][3] = 1;
}

void C_VECAdd(Vec* a, Vec* b, Vec* c)
{
    ASSERTMSGLINE(0x57, a, "VECAdd():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(0x58, b, "VECAdd():  NULL VecPtr 'b' ");
    ASSERTMSGLINE(0x59, c, "VECAdd():  NULL VecPtr 'ab' ");
    c->x = a->x + b->x;
    c->y = a->y + b->y;
    c->z = a->z + b->z;
}

void C_VECSubtract(Vec* a, Vec* b, Vec* c)
{
    ASSERTMSGLINE(0x9C, a, "VECSubtract():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(0x9D, b, "VECSubtract():  NULL VecPtr 'b' ");
    ASSERTMSGLINE(0x9E, c, "VECSubtract():  NULL VecPtr 'a_b' ");
    c->x = a->x - b->x;
    c->y = a->y - b->y;
    c->z = a->z - b->z;
}

void C_VECScale(Vec* src, Vec* dst, f32 scale)
{
    ASSERTMSGLINE(0xE2, src, "VECScale():  NULL VecPtr 'src' ");
    ASSERTMSGLINE(0xE3, dst, "VECScale():  NULL VecPtr 'dst' ");
    dst->x = (src->x * scale);
    dst->y = (src->y * scale);
    dst->z = (src->z * scale);
}

void C_VECNormalize(Vec* src, Vec* unit)
{
    f32 mag;

    ASSERTMSGLINE(0x127, src, "VECNormalize():  NULL VecPtr 'src' ");
    ASSERTMSGLINE(0x128, unit, "VECNormalize():  NULL VecPtr 'unit' ");
    mag = (src->z * src->z) + ((src->x * src->x) + (src->y * src->y));
    ASSERTMSGLINE(0x12D, 0.0f != mag,
                  "VECNormalize():  zero magnitude vector ");
    mag = 1.0f / sqrtf(mag);
    unit->x = src->x * mag;
    unit->y = src->y * mag;
    unit->z = src->z * mag;
}

f32 C_VECSquareMag(Vec* v)
{
    f32 sqmag;

    ASSERTMSGLINE(0x182, v, "VECMag():  NULL VecPtr 'v' ");

    sqmag = v->z * v->z + ((v->x * v->x) + (v->y * v->y));
    return sqmag;
}

f32 C_VECMag(Vec* v)
{
    return sqrtf(VECSquareMag(v));
}

f32 C_VECDotProduct(Vec* a, Vec* b)
{
    f32 dot;

    ASSERTMSGLINE(0x1D1, a, "VECDotProduct():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(0x1D2, b, "VECDotProduct():  NULL VecPtr 'b' ");
    dot = (a->z * b->z) + ((a->x * b->x) + (a->y * b->y));
    return dot;
}

void C_VECCrossProduct(Vec* a, Vec* b, Vec* axb)
{
    Vec vTmp;

    ASSERTMSGLINE(0x20F, a, "VECCrossProduct():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(0x210, b, "VECCrossProduct():  NULL VecPtr 'b' ");
    ASSERTMSGLINE(0x211, axb, "VECCrossProduct():  NULL VecPtr 'axb' ");

    vTmp.x = (a->y * b->z) - (a->z * b->y);
    vTmp.y = (a->z * b->x) - (a->x * b->z);
    vTmp.z = (a->x * b->y) - (a->y * b->x);
    axb->x = vTmp.x;
    axb->y = vTmp.y;
    axb->z = vTmp.z;
}

f32 C_VECSquareDistance(Vec* a, Vec* b)
{
    Vec diff;

    diff.x = a->x - b->x;
    diff.y = a->y - b->y;
    diff.z = a->z - b->z;
    return (diff.z * diff.z) + ((diff.x * diff.x) + (diff.y * diff.y));
}

void C_MTXMultVec(Mtx44 m, Vec* src, Vec* dst)
{
    Vec vTmp;

    ASSERTMSGLINE(0x39, m, "MTXMultVec():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x3A, src, "MTXMultVec():  NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x3B, dst, "MTXMultVec():  NULL MtxPtr 'dst' ");

    vTmp.x = m[0][3] +
             ((m[0][2] * src->z) + ((m[0][0] * src->x) + (m[0][1] * src->y)));
    vTmp.y = m[1][3] +
             ((m[1][2] * src->z) + ((m[1][0] * src->x) + (m[1][1] * src->y)));
    vTmp.z = m[2][3] +
             ((m[2][2] * src->z) + ((m[2][0] * src->x) + (m[2][1] * src->y)));
    dst->x = vTmp.x;
    dst->y = vTmp.y;
    dst->z = vTmp.z;
}

void C_MTXMultVecSR(Mtx44 m, Vec* src, Vec* dst)
{
    Vec vTmp;

    ASSERTMSGLINE(0x13A, m, "PSMTXMultVecSR():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0x13B, src, "PSMTXMultVecSR():  NULL MtxPtr 'src' ");
    ASSERTMSGLINE(0x13C, dst, "PSMTXMultVecSR():  NULL MtxPtr 'dst' ");
    vTmp.x = (m[0][2] * src->z) + ((m[0][0] * src->x) + (m[0][1] * src->y));
    vTmp.y = (m[1][2] * src->z) + ((m[1][0] * src->x) + (m[1][1] * src->y));
    vTmp.z = (m[2][2] * src->z) + ((m[2][0] * src->x) + (m[2][1] * src->y));
    dst->x = vTmp.x;
    dst->y = vTmp.y;
    dst->z = vTmp.z;
}

void C_MTXMultVecArray(Mtx m, Vec* srcBase, Vec* dstBase, u32 count)
{
    u32 i;
    Vec vTmp;

    ASSERTMSGLINE(0x9F, m, "MTXMultVecArray():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(0xA0, srcBase, "MTXMultVecArray():  NULL MtxPtr 'srcBase' ");
    ASSERTMSGLINE(0xA1, dstBase, "MTXMultVecArray():  NULL MtxPtr 'dstBase' ");

    for (i = 0; i < count; i++) {
        vTmp.x = m[0][3] + ((m[0][2] * srcBase->z) +
                            ((m[0][0] * srcBase->x) + (m[0][1] * srcBase->y)));
        vTmp.y = m[1][3] + ((m[1][2] * srcBase->z) +
                            ((m[1][0] * srcBase->x) + (m[1][1] * srcBase->y)));
        vTmp.z = m[2][3] + ((m[2][2] * srcBase->z) +
                            ((m[2][0] * srcBase->x) + (m[2][1] * srcBase->y)));
        dstBase->x = vTmp.x;
        dstBase->y = vTmp.y;
        dstBase->z = vTmp.z;
        srcBase++;
        dstBase++;
    }
}

void MTXFrustum(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f)
{
    f32 tmp;

    ASSERTMSGLINE(0x4C, m, "MTXFrustum():  NULL Mtx44Ptr 'm' ");
    ASSERTMSGLINE(0x4D, t != b,
                  "MTXFrustum():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(0x4E, l != r,
                  "MTXFrustum():  'l' and 'r' clipping planes are equal ");
    ASSERTMSGLINE(0x4F, n != f,
                  "MTXFrustum():  'n' and 'f' clipping planes are equal ");
    tmp = 1 / (r - l);
    m[0][0] = (2 * n * tmp);
    m[0][1] = 0;
    m[0][2] = (tmp * (r + l));
    m[0][3] = 0;
    tmp = 1 / (t - b);
    m[1][0] = 0;
    m[1][1] = (2 * n * tmp);
    m[1][2] = (tmp * (t + b));
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    tmp = 1 / (f - n);
    m[2][2] = (-n * tmp);
    m[2][3] = (tmp * -(f * n));
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = -1;
    m[3][3] = 0;
}

void MTXPerspective(Mtx m, f32 fovY, f32 aspect, f32 n, f32 f)
{
    f32 angle;
    f32 cot;
    f32 tmp;

    ASSERTMSGLINE(0x93, m, "MTXPerspective():  NULL Mtx44Ptr 'm' ");
    ASSERTMSGLINE(0x94, (fovY > 0.0) && (fovY < 180.0),
                  "MTXPerspective():  'fovY' out of range ");
    ASSERTMSGLINE(0x95, 0.0f != aspect, "MTXPerspective():  'aspect' is 0 ");

    angle = (0.5f * fovY);
    angle = angle * 0.017453293f;
    cot = 1 / tanf(angle);
    m[0][0] = (cot / aspect);
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = (cot);
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    tmp = 1 / (f - n);
    m[2][2] = (-n * tmp);
    m[2][3] = (tmp * -(f * n));
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = -1;
    m[3][3] = 0;
}

void MTXOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f)
{
    f32 tmp;

    ASSERTMSGLINE(0xDB, m, "MTXOrtho():  NULL Mtx44Ptr 'm' ");
    ASSERTMSGLINE(0xDC, t != b,
                  "MTXOrtho():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(0xDD, l != r,
                  "MTXOrtho():  'l' and 'r' clipping planes are equal ");
    ASSERTMSGLINE(0xDE, n != f,
                  "MTXOrtho():  'n' and 'f' clipping planes are equal ");
    tmp = 1 / (r - l);
    m[0][0] = 2 * tmp;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = (tmp * -(r + l));
    tmp = 1 / (t - b);
    m[1][0] = 0;
    m[1][1] = 2 * tmp;
    m[1][2] = 0;
    m[1][3] = (tmp * -(t + b));
    m[2][0] = 0;
    m[2][1] = 0;
    tmp = 1 / (f - n);
    m[2][2] = (-1 * tmp);
    m[2][3] = (-f * tmp);
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;
}

void GXProject(f32 x, f32 y, f32 z, f32 mtx[3][4], f32* pm, f32* vp, f32* sx,
               f32* sy, f32* sz)
{
    Vec peye;
    f32 xc;
    f32 yc;
    f32 zc;
    f32 wc;

    ASSERTMSGLINE(0x93, pm && vp && sx && sy && sz,
                  "GXGet*: invalid null pointer");

    peye.x =
        mtx[0][3] + ((mtx[0][2] * z) + ((mtx[0][0] * x) + (mtx[0][1] * y)));
    peye.y =
        mtx[1][3] + ((mtx[1][2] * z) + ((mtx[1][0] * x) + (mtx[1][1] * y)));
    peye.z =
        mtx[2][3] + ((mtx[2][2] * z) + ((mtx[2][0] * x) + (mtx[2][1] * y)));
    if (pm[0] == 0.0f) {
        xc = (peye.x * pm[1]) + (peye.z * pm[2]);
        yc = (peye.y * pm[3]) + (peye.z * pm[4]);
        zc = pm[6] + (peye.z * pm[5]);
        wc = 1.0f / -peye.z;
    } else {
        xc = pm[2] + (peye.x * pm[1]);
        yc = pm[4] + (peye.y * pm[3]);
        zc = pm[6] + (peye.z * pm[5]);
        wc = 1.0f;
    }
    *sx = (vp[2] / 2.0f) + (vp[0] + (wc * (xc * vp[2] / 2.0f)));
    *sy = (vp[3] / 2.0f) + (vp[1] + (wc * (-yc * vp[3] / 2.0f)));
    *sz = vp[5] + (wc * (zc * (vp[5] - vp[4])));
}
