ppm_load_read_header(FILE       *fp,
                     pnm_struct *img)
{
    
    gchar *ptr;
    
    gchar  header[MAX_CHARS_IN_ROW];
    gint   maxval;

    
    fgets (header,MAX_CHARS_IN_ROW,fp);

    if (header[0] != ASCII_P ||
        (header[1] != PIXMAP_ASCII &&
         header[1] != PIXMAP_RAW))
      {
        g_warning ("STR");
        return FALSE;
      }

    img->type = header[1];

    
    fgets (header,MAX_CHARS_IN_ROW,fp);
    while(header[0] == '#')
      {
        fgets (header,MAX_CHARS_IN_ROW,fp);
      }

    
    img->width  = strtol (header,&ptr,0);
    img->height = atoi (ptr);
    img->numsamples = img->width * img->height * CHANNEL_COUNT;

    fgets (header,MAX_CHARS_IN_ROW,fp);
    maxval = strtol (header,&ptr,0);

    if ((maxval != 255) && (maxval != 65535))
      {
        g_warning ("STR");
        return FALSE;
      }

  switch (maxval)
    {
    case 255:
      img->bpc = sizeof (guchar);
      break;

    case 65535:
      img->bpc = sizeof (gushort);
      break;

    default:
      g_warning ("STR", G_STRLOC);
    }

    return TRUE;
}