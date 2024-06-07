rsvg_filter_primitive_gaussian_blur_set_atts (RsvgNode * self,
                                              RsvgHandle * ctx, RsvgPropertyBag * atts)
{
    const char *value;
    RsvgFilterPrimitiveGaussianBlur *filter;

    filter = (RsvgFilterPrimitiveGaussianBlur *) self;

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
            rsvg_css_parse_number_optional_number (value, &filter->sdx, &filter->sdy);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            rsvg_defs_register_name (ctx->priv->defs, value, &filter->super.super);
    }
}