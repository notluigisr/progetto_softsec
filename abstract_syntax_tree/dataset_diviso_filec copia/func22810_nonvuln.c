rsvg_cairo_push_render_stack (RsvgDrawingCtx * ctx)
{
    

    RsvgCairoRender *render = (RsvgCairoRender *) ctx->render;
    cairo_surface_t *surface;
    cairo_t *child_cr;
    RsvgBbox *bbox;
    RsvgState *state = rsvg_current_state (ctx);
    gboolean lateclip = FALSE;

    if (rsvg_current_state (ctx)->clip_path_ref)
        if (((RsvgClipPath *) rsvg_current_state (ctx)->clip_path_ref)->units == objectBoundingBox)
            lateclip = TRUE;

    if (state->opacity == 0xFF
        && !state->filter && !state->mask && !lateclip && (state->comp_op == RSVG_COMP_OP_SRC_OVER)
        && (state->enable_background == RSVG_ENABLE_BACKGROUND_ACCUMULATE))
        return;
    if (!state->filter)
        surface = cairo_surface_create_similar (cairo_get_target (render->cr),
                                                CAIRO_CONTENT_COLOR_ALPHA,
                                                render->width, render->height);
    else {
        guchar *pixels;
        int rowstride = render->width * 4;
        GdkPixbuf *pixbuf;

        pixels = g_try_malloc0 (render->width * render->height * 4);
        if (pixels == NULL)
            return; 

        
        pixbuf = gdk_pixbuf_new_from_data (pixels,
                                           GDK_COLORSPACE_RGB,
                                           TRUE,
                                           8,
                                           render->width,
                                           render->height,
                                           rowstride,
                                           (GdkPixbufDestroyNotify) rsvg_pixmap_destroy,
                                           NULL);
        render->pixbuf_stack = g_list_prepend (render->pixbuf_stack, pixbuf);

        surface = cairo_image_surface_create_for_data (pixels,
                                                       CAIRO_FORMAT_ARGB32,
                                                       render->width, render->height, rowstride);
        
        cairo_surface_set_user_data (surface, &surface_pixel_data_key,
                                     g_object_ref (pixbuf),
                                     (cairo_destroy_func_t) g_object_unref);
    }
    child_cr = cairo_create (surface);
    cairo_surface_destroy (surface);

    render->cr_stack = g_list_prepend (render->cr_stack, render->cr);
    render->cr = child_cr;

    bbox = g_new (RsvgBbox, 1);
    *bbox = render->bbox;
    render->bb_stack = g_list_prepend (render->bb_stack, bbox);
    rsvg_bbox_init (&render->bbox, state->affine);
}