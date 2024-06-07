convert_1_bit (const gchar *src,
               gchar       *dst,
               guint32      rows,
               guint32      columns)
{

  guint32 row_pos = 0;
  gint    i, j;

  IFDBG(3)  g_debug ("STR");

  for (i = 0; i < rows * ((columns + 7) >> 3); ++i)
    {
      guchar    mask = 0x80;
      for (j = 0; j < 8 && row_pos < columns; ++j)
        {
          *dst = (*src & mask) ? 0 : 1;
          IFDBG(3) g_debug ("STR",
            i , j, row_pos, *src, *dst);
          dst++;
          mask >>= 1;
          row_pos++;
        }
      if (row_pos >= columns)
        row_pos = 0;
      src++;
    }
  IFDBG(3)  g_debug ("STR");
}