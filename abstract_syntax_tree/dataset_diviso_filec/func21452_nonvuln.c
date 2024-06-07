kate_type_find (GstTypeFind * tf, gpointer private)
{
  const guint8 *data = gst_type_find_peek (tf, 0, 64);
  gchar category[16] = { 0, };

  if (G_UNLIKELY (data == NULL))
    return;

  
  memcpy (category, data + 48, 15);
  GST_LOG ("STR", category);
  
  if (strcmp (category, "STR") == 0 ||
      strcmp (category, "STR") == 0 ||
      strcmp (category, "STR") == 0) {
    gst_type_find_suggest_simple (tf, GST_TYPE_FIND_MAXIMUM,
        "STR", NULL);
  } else {
    gst_type_find_suggest_simple (tf, GST_TYPE_FIND_MAXIMUM,
        "STR", NULL);
  }
}