gst_asf_demux_process_language_list (GstASFDemux * demux, guint8 * data,
    guint64 size)
{
  guint i;

  if (size < 2)
    goto not_enough_data;

  if (demux->languages) {
    GST_WARNING ("STR");
    g_strfreev (demux->languages);
    demux->languages = NULL;
    demux->num_languages = 0;
  }

  demux->num_languages = gst_asf_demux_get_uint16 (&data, &size);
  GST_LOG ("STR", demux->num_languages);

  demux->languages = g_new0 (gchar *, demux->num_languages + 1);
  for (i = 0; i < demux->num_languages; ++i) {
    guint8 len, *lang_data = NULL;

    if (size < 1)
      goto not_enough_data;
    len = gst_asf_demux_get_uint8 (&data, &size);
    if (gst_asf_demux_get_bytes (&lang_data, len, &data, &size)) {
      gchar *utf8;

      utf8 = g_convert ((gchar *) lang_data, len, "STR", NULL,
          NULL, NULL);

      
      if (utf8 && strlen (utf8) >= 5 && (utf8[2] == '-' || utf8[2] == '_')) {
        utf8[2] = '\0';
      }
      GST_DEBUG ("STR", i, GST_STR_NULL (utf8));
      demux->languages[i] = utf8;
      g_free (lang_data);
    } else {
      goto not_enough_data;
    }
  }

  return GST_FLOW_OK;

not_enough_data:
  {
    GST_WARNING_OBJECT (demux, "STR");
    g_free (demux->languages);
    demux->languages = NULL;
    demux->num_languages = 0;
    return GST_FLOW_OK;         
  }
}