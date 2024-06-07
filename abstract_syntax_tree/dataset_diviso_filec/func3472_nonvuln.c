rsvg_cairo_render_new (cairo_t * cr, double width, double height)
{
    RsvgCairoRender *cairo_render = g_new0 (RsvgCairoRender, 1);

    cairo_render->super.type = RSVG_RENDER_TYPE_CAIRO;
    cairo_render->super.free = rsvg_cairo_render_free;
    cairo_render->super.create_pango_context = rsvg_cairo_create_pango_context;
    cairo_render->super.render_pango_layout = rsvg_cairo_render_pango_layout;
    cairo_render->super.render_surface = rsvg_cairo_render_surface;
    cairo_render->super.render_path = rsvg_cairo_render_path;
    cairo_render->super.pop_discrete_layer = rsvg_cairo_pop_discrete_layer;
    cairo_render->super.push_discrete_layer = rsvg_cairo_push_discrete_layer;
    cairo_render->super.add_clipping_rect = rsvg_cairo_add_clipping_rect;
    cairo_render->super.get_surface_of_node = rsvg_cairo_get_surface_of_node;
    cairo_render->width = width;
    cairo_render->height = height;
    cairo_render->offset_x = 0;
    cairo_render->offset_y = 0;
    cairo_render->initial_cr = cr;
    cairo_render->cr = cr;
    cairo_render->cr_stack = NULL;
    cairo_render->bb_stack = NULL;
    cairo_render->surfaces_stack = NULL;

    return cairo_render;
}