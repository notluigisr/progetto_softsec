rsvg_start_extra (RsvgHandle * ctx,
                  const char *name,
                  GString **stringptr)
{
    RsvgSaxHandlerExtra *handler = g_new0 (RsvgSaxHandlerExtra, 1);
    RsvgNode *treebase = ctx->priv->treebase;
    RsvgNode *currentnode = ctx->priv->currentnode;
    gboolean do_care;

    
    do_care = treebase != NULL && treebase == currentnode;

    handler->super.free = rsvg_extra_handler_free;
    handler->super.characters = rsvg_extra_handler_characters;
    handler->super.start_element = rsvg_extra_handler_start;
    handler->super.end_element = rsvg_extra_handler_end;
    handler->ctx = ctx;
    handler->name = name; 
    handler->string = do_care ? g_string_new (NULL) : NULL;
    handler->stringptr = do_care ? stringptr : NULL;

    ctx->priv->handler = &handler->super;

    return handler;
}