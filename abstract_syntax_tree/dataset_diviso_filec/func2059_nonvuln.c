rsvg_metadata_handler_start (RsvgSaxHandler * self, const char *name, RsvgPropertyBag * atts)
{
    RsvgSaxHandlerMetadata *z = (RsvgSaxHandlerMetadata *) self;
    RsvgHandle *ctx = z->ctx;

    g_string_append_printf (ctx->priv->metadata, "STR", name);
    rsvg_property_bag_enumerate (atts, rsvg_metadata_props_enumerate, ctx->priv->metadata);
    g_string_append (ctx->priv->metadata, "STR");
}