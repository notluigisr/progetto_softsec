process (GeglOperation       *operation,
         GeglBuffer          *output,
         const GeglRectangle *result,
         gint                 level)
{
  GeglChantO   *o = GEGL_CHANT_PROPERTIES (operation);
  FILE         *fp;
  pnm_struct    img;
  GeglRectangle rect = {0,0,0,0};
  gboolean      ret = FALSE;

  fp = (!strcmp (o->path, "STR"));

  if (!fp)
    return FALSE;

  if (!ppm_load_read_header (fp, &img))
    goto out;

  rect.height = img.height;
  rect.width = img.width;

  
  img.data = (guchar*) g_malloc (img.numsamples * img.bpc);

  switch (img.bpc)
    {
    case 1:
      gegl_buffer_get (output, &rect, 1.0, babl_format ("STR"), img.data,
                       GEGL_AUTO_ROWSTRIDE, GEGL_ABYSS_NONE);
      break;

    case 2:
      gegl_buffer_get (output, &rect, 1.0, babl_format ("STR"), img.data,
                       GEGL_AUTO_ROWSTRIDE, GEGL_ABYSS_NONE);
      break;

    default:
      g_warning ("STR", G_STRLOC);
    }

  ppm_load_read_image (fp, &img);

  switch (img.bpc)
    {
    case 1:
      gegl_buffer_set (output, &rect, 0, babl_format ("STR"), img.data,
                       GEGL_AUTO_ROWSTRIDE);
      break;

    case 2:
      gegl_buffer_set (output, &rect, 0, babl_format ("STR"), img.data,
                       GEGL_AUTO_ROWSTRIDE);
      break;

    default:
      g_warning ("STR", G_STRLOC);
    }

  g_free (img.data);

  ret = TRUE;

 out:
  if (stdin != fp)
    fclose (fp);

  return ret;
}