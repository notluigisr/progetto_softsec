rsvg_filter_primitive_light_source_set_atts (RsvgNode * self,
                                             RsvgHandle * ctx, RsvgPropertyBag * atts)
{
    RsvgNodeLightSource *data;
    const char *value;

    data = (RsvgNodeLightSource *) self;

    if (rsvg_property_bag_size (atts)) {
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            data->azimuth = rsvg_css_parse_angle (value) / 180.0 * M_PI;
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            data->elevation = rsvg_css_parse_angle (value) / 180.0 * M_PI;
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            data->limitingconeAngle = rsvg_css_parse_angle (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            data->x = data->pointsAtX = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            data->y = data->pointsAtX = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            data->z = data->pointsAtX = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            data->pointsAtX = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            data->pointsAtY = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            data->pointsAtZ = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "STR")))
            data->specularExponent = g_ascii_strtod (value, NULL);
    }
}