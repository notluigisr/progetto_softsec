gst_mpegts_section_new (guint16 pid, guint8 * data, gsize data_size)
{
  GstMpegtsSection *res = NULL;
  guint8 tmp;
  guint8 table_id;
  guint16 section_length;

  
  section_length = GST_READ_UINT16_BE (data + 1) & 0x0FFF;
  if (G_UNLIKELY (data_size < section_length + 3))
    goto short_packet;

  
  table_id = *data;

  res = _gst_mpegts_section_init (pid, table_id);

  res->data = data;
  
  data++;
  
  res->short_section = (*data & 0x80) == 0x00;
  
  res->section_length = section_length + 3;
  if (!res->short_section) {
    
    res->crc = GST_READ_UINT32_BE (res->data + res->section_length - 4);
    
    data += 2;
    
    res->subtable_extension = GST_READ_UINT16_BE (data);
    data += 2;
    
    tmp = *data++;
    res->version_number = tmp >> 1 & 0x1f;
    res->current_next_indicator = tmp & 0x01;
    
    res->section_number = *data++;
    
    res->last_section_number = *data;
  }

  return res;

short_packet:
  {
    GST_WARNING
        ("STR" G_GSIZE_FORMAT
        "STR", pid, data_size, section_length + 3);
    g_free (data);
    return NULL;
  }
}