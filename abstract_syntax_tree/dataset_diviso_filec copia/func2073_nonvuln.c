rsvg_new_filter_primitive_gaussian_blur (void)
{
    RsvgFilterPrimitiveGaussianBlur *filter;
    filter = g_new (RsvgFilterPrimitiveGaussianBlur, 1);
    _rsvg_node_init (&filter->super.super, RSVG_NODE_TYPE_FILTER_PRIMITIVE_GAUSSIAN_BLUR);
    filter->super.in = g_string_new ("STR");
    filter->super.result = g_string_new ("STR");
    filter->super.x.factor = filter->super.y.factor = filter->super.width.factor =
        filter->super.height.factor = 'n';
    filter->sdx = 0;
    filter->sdy = 0;
    filter->super.render = &rsvg_filter_primitive_gaussian_blur_render;
    filter->super.super.free = &rsvg_filter_primitive_gaussian_blur_free;
    filter->super.super.set_atts = rsvg_filter_primitive_gaussian_blur_set_atts;
    return (RsvgNode *) filter;
}