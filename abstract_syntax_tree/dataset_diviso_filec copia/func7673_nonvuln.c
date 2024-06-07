void nbd_client_new(NBDExport *exp,
                    QIOChannelSocket *sioc,
                    QCryptoTLSCreds *tlscreds,
                    const char *tlsaclname,
                    void (*close_fn)(NBDClient *, bool))
{
    NBDClient *client;
    Coroutine *co;

    client = g_malloc0(sizeof(NBDClient));
    client->refcount = 1;
    client->exp = exp;
    client->tlscreds = tlscreds;
    if (tlscreds) {
        object_ref(OBJECT(client->tlscreds));
    }
    client->tlsaclname = g_strdup(tlsaclname);
    client->sioc = sioc;
    object_ref(OBJECT(client->sioc));
    client->ioc = QIO_CHANNEL(sioc);
    object_ref(OBJECT(client->ioc));
    client->close_fn = close_fn;

    co = qemu_coroutine_create(nbd_co_client_start, client);
    qemu_coroutine_enter(co);
}