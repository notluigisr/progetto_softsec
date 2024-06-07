_set_rsvg_affine (RsvgCairoRender * render, const double affine[6])
{
    cairo_t * cr = render->cr;
    cairo_matrix_t matrix;
    gboolean nest = cr != render->initial_cr;

    cairo_matrix_init (&matrix,
                       affine[0], affine[1],
                       affine[2], affine[3],
                       affine[4] + (nest ? 0 : render->offset_x),
                       affine[5] + (nest ? 0 : render->offset_y));
    cairo_set_matrix (cr, &matrix);
}