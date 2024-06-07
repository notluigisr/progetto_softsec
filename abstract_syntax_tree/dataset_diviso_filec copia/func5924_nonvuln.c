static INLINE int SFTP_GetSz(byte* buf, word32* sz,
        word32 lowerBound, word32 upperBound)
{
    int ret = WS_SUCCESS;

    if (buf == NULL || sz == NULL) {
        ret = WS_BAD_ARGUMENT;
    }

    if (ret == WS_SUCCESS) {
        word32 val;

        ato32(buf, &val);
        if (val < lowerBound || val > upperBound)
            ret = WS_BUFFER_E;
        else
            *sz = val;
    }

    return ret;
}