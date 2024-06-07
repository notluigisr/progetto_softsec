static int nbd_negotiate_send_rep_len(QIOChannel *ioc, uint32_t type,
                                      uint32_t opt, uint32_t len)
{
    uint64_t magic;

    TRACE("STR" PRIu32,
          type, opt, len);

    magic = cpu_to_be64(NBD_REP_MAGIC);
    if (nbd_negotiate_write(ioc, &magic, sizeof(magic)) < 0) {
        LOG("STR");
        return -EINVAL;
    }
    opt = cpu_to_be32(opt);
    if (nbd_negotiate_write(ioc, &opt, sizeof(opt)) < 0) {
        LOG("STR");
        return -EINVAL;
    }
    type = cpu_to_be32(type);
    if (nbd_negotiate_write(ioc, &type, sizeof(type)) < 0) {
        LOG("STR");
        return -EINVAL;
    }
    len = cpu_to_be32(len);
    if (nbd_negotiate_write(ioc, &len, sizeof(len)) < 0) {
        LOG("STR");
        return -EINVAL;
    }
    return 0;
}