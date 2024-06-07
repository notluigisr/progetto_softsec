_rsvg_node_poly_set_atts (RsvgNode * self, RsvgHandle * ctx, RsvgPropertyBag * atts)
{
    RsvgNodePoly *poly = (RsvgNodePoly *) self;
    const char *klazz = NULL, *id = NULL, *value;

    if (rsvg_property_bag_size (atts)) {
        
        if ((value = rsvg_property_bag_lookup (atts, "STR"))
            || (value = rsvg_property_bag_lookup (atts, "STR"))) {
            if (poly->path)
                rsvg_cairo_path_destroy (poly->path);
            poly->path = _rsvg_node_poly_build_path (value,
                                                     RSVG_NODE_TYPE (self) == RSVG_NODE_TYPE_POLYGON);
        }
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            klazz = value;
        if ((value = rsvg_property_bag_lookup (atts, "STR"))) {
            id = value;
            rsvg_defs_register_name (ctx->priv->defs, value, self);
        }

        rsvg_parse_style_attrs (ctx, self->state,
                                RSVG_NODE_TYPE (self) == RSVG_NODE_TYPE_POLYLINE ? "STR",
                                klazz, id, atts);
    }

}