static void blk_aio_attached(AioContext *ctx, void *opaque)
{
    NBDExport *exp = opaque;
    NBDClient *client;

    TRACE("STR", exp->name, ctx);

    exp->ctx = ctx;

    QTAILQ_FOREACH(client, &exp->clients, next) {
        qio_channel_attach_aio_context(client->ioc, ctx);
        if (client->recv_coroutine) {
            aio_co_schedule(ctx, client->recv_coroutine);
        }
        if (client->send_coroutine) {
            aio_co_schedule(ctx, client->send_coroutine);
        }
    }
}