ico_load_thumbnail_image (const gchar  *filename,
                          gint         *width,
                          gint         *height,
                          GError      **error)
{
  FILE        *fp;
  IcoLoadInfo *info;
  gint32       image;
  gint         w     = 0;
  gint         h     = 0;
  gint         bpp   = 0;
  gint         match = 0;
  gint         i, icon_count;
  guchar      *buffer;

  gimp_progress_init_printf (_("STR"),
                             gimp_filename_to_utf8 (filename));

  fp = g_fopen (filename, "STR");
  if (! fp )
    {
      g_set_error (error, G_FILE_ERROR, g_file_error_from_errno (errno),
                   _("STR"),
                   gimp_filename_to_utf8 (filename), g_strerror (errno));
      return -1;
    }

  icon_count = ico_read_init (fp);
  if (! icon_count )
    {
      fclose (fp);
      return -1;
    }

  D(("STR",
     filename, icon_count));

  info = ico_read_info (fp, icon_count);
  if (! info )
    {
      fclose (fp);
      return -1;
    }

  
  for (i = 0; i < icon_count; i++)
    {
      if ((info[i].width  > w && w < *width) ||
          (info[i].height > h && h < *height))
        {
          w = info[i].width;
          h = info[i].height;
          bpp = info[i].bpp;

          match = i;
        }
      else if ( w == info[i].width
                && h == info[i].height
                && info[i].bpp > bpp )
        {
          
          bpp = info[i].bpp;
          match = i;
        }
    }

  if (w <= 0 || h <= 0)
    return -1;

  image = gimp_image_new (w, h, GIMP_RGB);
  buffer = g_new (guchar, w*h*4);
  ico_load_layer (fp, image, match, buffer, w*h*4, info+match);
  g_free (buffer);

  *width  = w;
  *height = h;

  D(("STR"));

  gimp_progress_update (1.0);

  g_free (info);
  fclose (fp);

  return image;
}