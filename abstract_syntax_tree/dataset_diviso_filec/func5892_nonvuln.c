test_instancing_limit (gconstpointer data)
{
    const char *basename = data;
    char *filename = get_test_filename (basename);
    RsvgHandle *handle;
    GError *error = NULL;
    cairo_surface_t *surf;
    cairo_t *cr;

    handle = rsvg_handle_new_from_file (filename, &error);
    g_free (filename);
    g_assert (handle != NULL);
    g_assert (error == NULL);

    surf = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 1, 11);
    cr = cairo_create (surf);

    g_assert (!rsvg_handle_render_cairo (handle, cr));

    g_object_unref (handle);
}