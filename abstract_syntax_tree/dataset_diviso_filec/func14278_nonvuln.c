    if (ret == WS_SUCCESS) {
        WMEMSET((byte*)&fd, 0, sizeof(HANDLE));
        WMEMCPY((byte*)&fd, data + idx, sz);
        idx += sz;

        
        WMEMSET(&offset, 0, sizeof(OVERLAPPED));
        ato32(data + idx, &sz);
        idx += UINT32_SZ;
        offset.OffsetHigh = (DWORD)sz;
        ato32(data + idx, &sz);
        idx += UINT32_SZ;
        offset.Offset = (DWORD)sz;

        
        ato32(data + idx, &sz);
        idx += UINT32_SZ;
        if (sz > maxSz - idx) {
            return WS_BUFFER_E;
        }

        if (WriteFile(fd, data + idx, sz, &bytesWritten, &offset) == 0) {
            WLOG(WS_LOG_SFTP, "STR");
            res  = err;
            type = WOLFSSH_FTP_FAILURE;
            ret  = WS_INVALID_STATE_E;
        }
        else {
            ret = WS_SUCCESS;
        }
    }