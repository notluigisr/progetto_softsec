rsvg_filter_primitive_tile_set_atts (RsvgNode * self, RsvgHandle * ctx, RsvgPropertyBag * atts)
{
    const char *value;
    RsvgFilterPrimitiveTile *filter;

    filter = (RsvgFilterPrimitiveTile *) self;

    if (rsvg_property_bag_size (atts)) {
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            g_string_assign (filter->super.in, value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            g_string_assign (filter->super.result, value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            filter->super.x = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            filter->super.y = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            filter->super.width = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            filter->super.height = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            rsvg_defs_register_name (ctx->priv->defs, value, &filter->super.super);
    }
}