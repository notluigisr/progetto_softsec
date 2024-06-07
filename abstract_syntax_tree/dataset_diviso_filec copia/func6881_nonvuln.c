gdk_pixbuf_serialize (GIcon *icon)
{
  GError *error = NULL;
  GVariant *result;
  GBytes *bytes;

  bytes = gdk_pixbuf_make_bytes (GDK_PIXBUF (icon), &error);
  if (!bytes)
    {
      g_critical ("STR", error->message);
      g_error_free (error);
      return NULL;
    }
  result = g_variant_new_from_bytes (G_VARIANT_TYPE_BYTESTRING, bytes, TRUE);
  g_bytes_unref (bytes);

  return g_variant_new ("STR", result);
}