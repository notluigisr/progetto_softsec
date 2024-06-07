rsvg_filter_primitive_image_free (RsvgNode * self)
{
    RsvgFilterPrimitiveImage *upself;

    upself = (RsvgFilterPrimitiveImage *) self;
    g_string_free (upself->super.result, TRUE);
    g_string_free (upself->super.in, TRUE);

    if (upself->href)
        g_string_free (upself->href, TRUE);

    _rsvg_node_free (self);
}