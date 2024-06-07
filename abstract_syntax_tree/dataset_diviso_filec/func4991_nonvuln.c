rsvg_paint_server_rad_grad (RsvgRadialGradient * gradient)
{
    RsvgPaintServer *result = g_new (RsvgPaintServer, 1);

    result->refcnt = 1;
    result->type = RSVG_PAINT_SERVER_RAD_GRAD;
    result->core.radgrad = gradient;

    return result;
}