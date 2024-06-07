int wolfSSH_SFTP_CreateStatus(WOLFSSH* ssh, word32 status, word32 reqId,
        const char* reason, const char* lang, byte* out, word32* outSz)
{
    word32 sz;
    word32 maxSz;
    word32 idx = 0;

    if (ssh == NULL || outSz == NULL) {
        return WS_BAD_ARGUMENT;
    }

    maxSz = WOLFSSH_SFTP_HEADER + (UINT32_SZ * 3);
    if (reason != NULL) {
        maxSz += (word32)WSTRLEN(reason);
    }
    if (lang != NULL) {
        maxSz += (word32)WSTRLEN(lang);
    }

    if (out == NULL) {
        *outSz = maxSz;
        return WS_SIZE_ONLY;
    }

    if (maxSz > *outSz) {
        WLOG(WS_LOG_SFTP, "STR");
        return WS_BUFFER_E;
    }

    idx += WOLFSSH_SFTP_HEADER;
    if (SFTP_SetHeader(ssh, reqId, WOLFSSH_FTP_STATUS, maxSz - idx, out)
            != WS_SUCCESS) {
        return WS_FATAL_ERROR;
    }
    c32toa(status, out + idx); idx += UINT32_SZ;

    sz = (reason != NULL)? (int)WSTRLEN(reason): 0;
    if (sz + idx + UINT32_SZ > maxSz) {
        return WS_BUFFER_E;
    }

    c32toa(sz, out + idx); idx += UINT32_SZ;
    if (reason != NULL) {
        WMEMCPY(out + idx, reason, sz); idx += sz;
    }

    sz = (lang != NULL)? (int)WSTRLEN(lang): 0;
    if (sz + idx + UINT32_SZ > maxSz) {
        return WS_BUFFER_E;
    }

    c32toa(sz, out + idx); idx += UINT32_SZ;
    if (lang != NULL) {
        WMEMCPY(out + idx, lang, sz);
    }
    *outSz = idx + sz;

    return WS_SUCCESS;
}