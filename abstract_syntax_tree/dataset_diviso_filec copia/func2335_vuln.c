rsvg_characters_impl (RsvgHandle * ctx, const xmlChar * ch, int len)
{
    RsvgNodeChars *self;

    if (!ch || !len)
        return;

    if (ctx->priv->currentnode) {
        if (!strcmp ("STR", ctx->priv->currentnode->type->str) ||
            !strcmp ("STR", ctx->priv->currentnode->type->str)) {
            guint i;

            
            self = NULL;
            for (i = 0; i < ctx->priv->currentnode->children->len; i++) {
                RsvgNode *node = g_ptr_array_index (ctx->priv->currentnode->children, i);
                if (!strcmp (node->type->str, "STR")) {
                    self = (RsvgNodeChars*)node;
                }
            }

            if (self != NULL) {
                if (!g_utf8_validate ((char *) ch, len, NULL)) {
                    char *utf8;
                    utf8 = rsvg_make_valid_utf8 ((char *) ch, len);
                    g_string_append (self->contents, utf8);
                    g_free (utf8);
                } else {
                    g_string_append_len (self->contents, (char *)ch, len);
                }

                return;
            }
        }
    }

    self = g_new (RsvgNodeChars, 1);
    _rsvg_node_init (&self->super);

    if (!g_utf8_validate ((char *) ch, len, NULL)) {
        char *utf8;
        utf8 = rsvg_make_valid_utf8 ((char *) ch, len);
        self->contents = g_string_new (utf8);
        g_free (utf8);
    } else {
        self->contents = g_string_new_len ((char *) ch, len);
    }

    self->super.type = g_string_new ("STR");
    self->super.free = _rsvg_node_chars_free;
    self->super.state->cond_true = FALSE;

    rsvg_defs_register_memory (ctx->priv->defs, (RsvgNode *) self);
    if (ctx->priv->currentnode)
        rsvg_node_group_pack (ctx->priv->currentnode, (RsvgNode *) self);
}