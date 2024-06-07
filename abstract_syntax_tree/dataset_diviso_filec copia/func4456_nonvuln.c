static int nbd_negotiate_send_info(NBDClient *client, uint32_t opt,
                                   uint16_t info, uint32_t length, void *buf,
                                   Error **errp)
{
    int rc;

    trace_nbd_negotiate_send_info(info, nbd_info_lookup(info), length);
    rc = nbd_negotiate_send_rep_len(client->ioc, NBD_REP_INFO, opt,
                                    sizeof(info) + length, errp);
    if (rc < 0) {
        return rc;
    }
    cpu_to_be16s(&info);
    if (nbd_write(client->ioc, &info, sizeof(info), errp) < 0) {
        return -EIO;
    }
    if (nbd_write(client->ioc, buf, length, errp) < 0) {
        return -EIO;
    }
    return 0;
}