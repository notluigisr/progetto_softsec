read_channel_data (PSDchannel     *channel,
                   const guint16   bps,
                   const guint16   compression,
                   const guint16  *rle_pack_len,
                   FILE           *f,
                   GError        **error)
{
  gchar    *raw_data;
  gchar    *src;
  gchar    *dst;
  guint32   readline_len;
  gint      i;

  if (bps == 1)
    readline_len = ((channel->columns + 7) >> 3);
  else
    readline_len = (channel->columns * bps >> 3);

  IFDBG(3) g_debug ("STR", readline_len,
                    channel->rows, readline_len * channel->rows);
  raw_data = g_malloc (readline_len * channel->rows);
  switch (compression)
    {
      case PSD_COMP_RAW:
        if (fread (raw_data, readline_len, channel->rows, f) < 1)
          {
            psd_set_error (feof (f), errno, error);
            return -1;
          }
        break;

      case PSD_COMP_RLE:
        for (i = 0; i < channel->rows; ++i)
          {
            src = g_malloc (rle_pack_len[i]);
            dst = g_malloc (readline_len);

            if (fread (src, rle_pack_len[i], 1, f) < 1)
              {
                psd_set_error (feof (f), errno, error);
                return -1;
              }
            
            decode_packbits (src, dst, rle_pack_len[i], readline_len);
            g_free (src);
            memcpy (raw_data + i * readline_len, dst, readline_len);
            g_free (dst);
          }
        break;
    }

  
  switch (bps)
    {
      case 16:
        channel->data = (gchar *) g_malloc (channel->rows * channel->columns);
        convert_16_bit (raw_data, channel->data, (channel->rows * channel->columns) << 1);
        break;

      case 8:
        channel->data = (gchar *) g_malloc (channel->rows * channel->columns);
        memcpy (channel->data, raw_data, (channel->rows * channel->columns));
        break;

      case 1:
        channel->data = (gchar *) g_malloc (channel->rows * channel->columns);
        convert_1_bit (raw_data, channel->data, channel->rows, channel->columns);
        break;
    }

  g_free (raw_data);

  return 1;
}