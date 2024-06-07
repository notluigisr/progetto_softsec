gdk_pixbuf_set_property (GObject         *object,
			 guint            prop_id,
			 const GValue    *value,
			 GParamSpec      *pspec)
{
  GdkPixbuf *pixbuf = GDK_PIXBUF (object);

  switch (prop_id)
          {
          case PROP_COLORSPACE:
                  pixbuf->colorspace = g_value_get_enum (value);
                  break;
          case PROP_N_CHANNELS:
                  pixbuf->n_channels = g_value_get_int (value);
                  break;
          case PROP_HAS_ALPHA:
                  pixbuf->has_alpha = g_value_get_boolean (value);
                  break;
          case PROP_BITS_PER_SAMPLE:
                  pixbuf->bits_per_sample = g_value_get_int (value);
                  break;
          case PROP_WIDTH:
                  pixbuf->width = g_value_get_int (value);
                  break;
          case PROP_HEIGHT:
                  pixbuf->height = g_value_get_int (value);
                  break;
          case PROP_ROWSTRIDE:
                  pixbuf->rowstride = g_value_get_int (value);
                  break;
          case PROP_PIXELS:
                  pixbuf->pixels = (guchar *) g_value_get_pointer (value);
                  break;
          default:
                  G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                  break;
          }
}