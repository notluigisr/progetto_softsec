_set_source_rsvg_solid_colour (RsvgDrawingCtx * ctx,
                               RsvgSolidColour * colour, guint8 opacity, guint32 current_colour)
{
    cairo_t *cr = ((RsvgCairoRender *) ctx->render)->cr;
    guint32 rgb = colour->rgb;
    double r, g, b;

    if (colour->currentcolour)
        rgb = current_colour;

    r = ((rgb >> 16) & 0xff) / 255.0;
    g = ((rgb >> 8) & 0xff) / 255.0;
    b = ((rgb >> 0) & 0xff) / 255.0;

    if (opacity == 0xff)
        cairo_set_source_rgb (cr, r, g, b);
    else
        cairo_set_source_rgba (cr, r, g, b, opacity / 255.0);
}