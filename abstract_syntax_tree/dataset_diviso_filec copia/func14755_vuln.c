static int nbd_negotiate_handle_export_name(NBDClient *client, uint32_t length)
{
    int rc = -EINVAL;
    char name[NBD_MAX_NAME_SIZE + 1];

    
    TRACE("STR");
    if (length >= sizeof(name)) {
        LOG("STR");
        goto fail;
    }
    if (nbd_negotiate_read(client->ioc, name, length) < 0) {
        LOG("STR");
        goto fail;
    }
    name[length] = '\0';

    TRACE("STR", name);

    client->exp = nbd_export_find(name);
    if (!client->exp) {
        LOG("STR");
        goto fail;
    }

    QTAILQ_INSERT_TAIL(&client->exp->clients, client, next);
    nbd_export_get(client->exp);
    rc = 0;
fail:
    return rc;
}