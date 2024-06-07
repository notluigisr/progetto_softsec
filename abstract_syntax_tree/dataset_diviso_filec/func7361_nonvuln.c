gst_asf_demux_get_gst_tag_from_tag_name (const gchar * name_utf8)
{
  const struct
  {
    const gchar *asf_name;
    const gchar *gst_name;
  } tags[] = {
    {
    "STR", GST_TAG_GENRE}, {
    "STR", GST_TAG_ALBUM}, {
    "STR", GST_TAG_ARTIST}, {
    "STR", GST_TAG_IMAGE}, {
    "STR", GST_TAG_TRACK_NUMBER}, {
    "STR", GST_TAG_TRACK_NUMBER}, {
    "STR", GST_TAG_DATE_TIME}
    
  };
  gsize out;
  guint i;

  if (name_utf8 == NULL) {
    GST_WARNING ("STR");
    return NULL;
  }

  out = strlen (name_utf8);

  for (i = 0; i < G_N_ELEMENTS (tags); ++i) {
    if (strncmp (tags[i].asf_name, name_utf8, out) == 0) {
      GST_LOG ("STR", name_utf8, tags[i].gst_name);
      return tags[i].gst_name;
    }
  }

  return NULL;
}