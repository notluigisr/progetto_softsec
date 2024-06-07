gdk_pixbuf_get_has_alpha (const GdkPixbuf *pixbuf)
{
	g_return_val_if_fail (GDK_IS_PIXBUF (pixbuf), FALSE);

	return pixbuf->has_alpha ? TRUE : FALSE;
}