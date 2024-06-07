rsvg_characters (void *data, const xmlChar * ch, int len)
{
    RsvgHandle *ctx = (RsvgHandle *) data;

    if (ctx->priv->handler && ctx->priv->handler->characters != NULL) {
        ctx->priv->handler->characters (ctx->priv->handler, (const char *) ch, len);
        return;
    }

    rsvg_characters_impl (ctx, ch, len);
}