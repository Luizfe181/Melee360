/* Generated original blocks. delay.c SHA256: 384997473A6ECF642C31F418B13BD8CCAF628D451E97480FE7E6FCF9CE98D9C5; axfx.c SHA256: ECAB1EBFA3489EB40A37893CB9DC8BA1C1BCBD7538D458E7F178530451649A6D */
void AXFXDelayCallback(struct AXFX_BUFFERUPDATE* bufferUpdate,
                       struct AXFX_DELAY* delay)
{
    long l;
    long r;
    long s;
    long* lBuf;
    long* rBuf;
    long* sBuf;
    u32 i;
    long* left;
    long* right;
    long* sur;

    left = bufferUpdate->left;
    right = bufferUpdate->right;
    sur = bufferUpdate->surround;
    lBuf = delay->left + (delay->currentPos[0] * 0xA0);
    rBuf = delay->right + (delay->currentPos[1] * 0xA0);
    sBuf = delay->sur + (delay->currentPos[2] * 0xA0);

    for (i = 0; i < 160; i++) {
        l = *lBuf;
        r = *rBuf;
        s = *sBuf;
        *lBuf++ = *left + ((s32) (l * delay->currentFeedback[0]) >> 7);
        *rBuf++ = *right + ((s32) (r * delay->currentFeedback[1]) >> 7);
        *sBuf++ = *sur + ((s32) (s * delay->currentFeedback[2]) >> 7);
        *left++ = (s32) (l * delay->currentOutput[0]) >> 7;
        *right++ = (s32) (r * delay->currentOutput[1]) >> 7;
        *sur++ = (s32) (s * delay->currentOutput[2]) >> 7;
    }
    delay->currentPos[0] =
        (s32) ((delay->currentPos[0] + 1) % delay->currentSize[0]);
    delay->currentPos[1] =
        (s32) ((delay->currentPos[1] + 1) % delay->currentSize[1]);
    delay->currentPos[2] =
        (s32) ((delay->currentPos[2] + 1) % delay->currentSize[2]);
}
void AXFXSetHooks(void* (*alloc_hook)(unsigned long), void (*free_hook)(void*))
{
    __AXFXAlloc = alloc_hook;
    __AXFXFree = free_hook;
}
