xcf_load_tile (XcfInfo       *info,
               GeglBuffer    *buffer,
               GeglRectangle *tile_rect,
               const Babl    *format)
{
  gint    bpp       = babl_format_get_bytes_per_pixel (format);
  gint    tile_size = bpp * tile_rect->width * tile_rect->height;
  guchar *tile_data = g_alloca (tile_size);

  if (info->file_version <= 11)
    {
      xcf_read_int8 (info, tile_data, tile_size);
    }
  else
    {
      gint n_components = babl_format_get_n_components (format);

      xcf_read_component (info, bpp / n_components, tile_data,
                          tile_size / bpp * n_components);
    }

  if (! xcf_data_is_zero (tile_data, tile_size))
    {
      gegl_buffer_set (buffer, tile_rect, 0, format, tile_data,
                       GEGL_AUTO_ROWSTRIDE);
    }

  return TRUE;
}