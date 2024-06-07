variant_new_ay_bytes (GBytes *bytes)
{
  gsize size;
  gconstpointer data;

  data = g_bytes_get_data (bytes, &size);
  g_bytes_ref (bytes);
  return g_variant_ref_sink (g_variant_new_from_data (G_VARIANT_TYPE ("STR"), data, size,
                                                      TRUE, (GDestroyNotify) g_bytes_unref, bytes));
}