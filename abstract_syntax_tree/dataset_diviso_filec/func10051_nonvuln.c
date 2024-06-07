ico_read_info (FILE    *fp,
               gint     icon_count,
               GError **error)
{
  gint            i;
  IcoFileEntry   *entries;
  IcoLoadInfo    *info;

  
  entries = g_new (IcoFileEntry, icon_count);
  if (fread (entries, sizeof (IcoFileEntry), icon_count, fp) <= 0)
    {
      g_set_error (error, G_FILE_ERROR, 0,
                   _("STR"),
                   sizeof (IcoFileEntry));
      g_free (entries);
      return NULL;
    }

  info = g_new (IcoLoadInfo, icon_count);
  for (i = 0; i < icon_count; i++)
    {
      info[i].width  = entries[i].width;
      info[i].height = entries[i].height;
      info[i].bpp    = GUINT16_FROM_LE (entries[i].bpp);
      info[i].size   = GUINT32_FROM_LE (entries[i].size);
      info[i].offset = GUINT32_FROM_LE (entries[i].offset);

      if (info[i].width == 0 || info[i].height == 0)
        {
          ico_read_size (fp, info + i);
        }

      D(("STR",
         info[i].width, info[i].height, info[i].bpp,
         info[i].size, info[i].offset));

      if (info[i].width == 0 || info[i].height == 0)
        {
          g_set_error (error, G_FILE_ERROR, 0,
                       _("STR"), i);
          g_free (info);
          g_free (entries);
          return NULL;
        }
    }

  g_free (entries);

  return info;
}