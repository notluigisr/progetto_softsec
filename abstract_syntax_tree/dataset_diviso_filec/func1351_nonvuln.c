h263_video_type_find (GstTypeFind * tf, gpointer unused)
{
  DataScanCtx c = { 0, NULL, 0 };
  guint64 data = 0xffff;        
  guint64 psc = 0;
  guint8 ptype = 0;
  guint format;
  guint good = 0;
  guint bad = 0;
  guint pc_type, pb_mode;

  while (c.offset < H263_MAX_PROBE_LENGTH) {
    if (G_UNLIKELY (!data_scan_ctx_ensure_data (tf, &c, 4)))
      break;

    
    data = (data << 8) + c.data[0];
    psc = data & G_GUINT64_CONSTANT (0xfffffc0000);
    if (psc == 0x800000) {
      
      
      ptype = (data & 0x3fc) >> 2;
      
      format = ptype & 0x07;

      
      if (((ptype >> 6) == 0x2) && (format > 0 && format < 6)) {
        pc_type = data & 0x02;
        pb_mode = c.data[1] & 0x20 >> 4;
        if (!pc_type && pb_mode)
          bad++;
        else
          good++;
      } else
        bad++;

      
    }

    data_scan_ctx_advance (tf, &c, 1);
  }

  GST_LOG ("STR", good, bad);

  if (good > 2 * bad)
    gst_type_find_suggest (tf, GST_TYPE_FIND_POSSIBLE, H263_VIDEO_CAPS);

  return;
}