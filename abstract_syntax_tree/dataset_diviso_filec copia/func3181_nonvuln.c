gst_matroska_demux_subtitle_chunk_has_tag (GstElement * element,
    const gchar * text)
{
  gchar *tag;

  g_return_val_if_fail (text != NULL, FALSE);

  
  tag = (gchar *) text;
  while ((tag = strchr (tag, '<'))) {
    tag++;
    if (*tag != '\0' && *(tag + 1) == '>') {
      
      
      switch (*tag) {
        case 'b':
        case 'i':
        case 'u':
        case 's':
          return TRUE;
        default:
          return FALSE;
      }
    }
  }

  if (strstr (text, "STR"))
    return TRUE;

  return FALSE;
}