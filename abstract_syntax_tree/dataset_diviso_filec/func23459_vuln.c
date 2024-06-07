    if (sz + idx > maxSz || sz > WOLFSSH_MAX_HANDLE) {
        WLOG(WS_LOG_SFTP, "STR");
        res  = err;
        type = WOLFSSH_FTP_FAILURE;
        ret  = WS_BAD_FILE_E;
    }