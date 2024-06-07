nbd_negotiate_send_rep_err(QIOChannel *ioc, uint32_t type,
                           uint32_t opt, const char *fmt, ...)
{
    va_list va;
    char *msg;
    int ret;
    size_t len;

    va_start(va, fmt);
    msg = g_strdup_vprintf(fmt, va);
    va_end(va);
    len = strlen(msg);
    assert(len < 4096);
    TRACE("STR", msg);
    ret = nbd_negotiate_send_rep_len(ioc, type, opt, len);
    if (ret < 0) {
        goto out;
    }
    if (nbd_negotiate_write(ioc, msg, len) < 0) {
        LOG("STR");
        ret = -EIO;
    } else {
        ret = 0;
    }
out:
    g_free(msg);
    return ret;
}