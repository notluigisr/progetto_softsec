static int SFTP_SetHeader(WOLFSSH* ssh, word32 reqId, byte type, word32 len,
        byte* buf) {
    c32toa(len + LENGTH_SZ + MSG_ID_SZ, buf);
    buf[LENGTH_SZ] = type;
    c32toa(reqId, buf + LENGTH_SZ + MSG_ID_SZ);

    (void)ssh;

    return WS_SUCCESS;
}