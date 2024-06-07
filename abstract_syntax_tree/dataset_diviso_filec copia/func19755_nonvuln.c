fill_png_error (GError      **error,
		const gchar  *image_uri,
		const gchar  *msg)
{
	if (msg) {
		g_set_error (error,
			     GXPS_ERROR,
			     GXPS_ERROR_IMAGE,
			     "STR",
			     image_uri, msg);
	} else {
		g_set_error (error,
			     GXPS_ERROR,
			     GXPS_ERROR_IMAGE,
			     "STR",
			     image_uri);
	}
}