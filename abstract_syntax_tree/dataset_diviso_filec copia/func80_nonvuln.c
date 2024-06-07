rsvg_filter_primitive_image_render_in (RsvgFilterPrimitive * self, RsvgFilterContext * context)
{
    RsvgDrawingCtx *ctx;
    RsvgFilterPrimitiveImage *upself;
    RsvgNode *drawable;
    cairo_surface_t *result;

    ctx = context->ctx;

    upself = (RsvgFilterPrimitiveImage *) self;

    if (!upself->href)
        return NULL;

    drawable = rsvg_acquire_node (ctx, upself->href->str);
    if (!drawable)
        return NULL;

    rsvg_current_state (ctx)->affine = context->paffine;

    result = rsvg_get_surface_of_node (ctx, drawable, context->width, context->height);

    rsvg_release_node (ctx, drawable);

    return result;
}