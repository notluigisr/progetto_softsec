_parse_pat (GstMpegtsSection * section)
{
  GPtrArray *pat;
  guint16 i = 0, nb_programs;
  GstMpegtsPatProgram *program;
  guint8 *data, *end;

  
  data = section->data + 8;

  
  end = section->data + section->section_length;

  
  nb_programs = (end - 4 - data) / 4;
  pat =
      g_ptr_array_new_full (nb_programs,
      (GDestroyNotify) _mpegts_pat_program_free);

  while (data < end - 4) {
    program = g_slice_new0 (GstMpegtsPatProgram);
    program->program_number = GST_READ_UINT16_BE (data);
    data += 2;

    program->network_or_program_map_PID = GST_READ_UINT16_BE (data) & 0x1FFF;
    data += 2;

    g_ptr_array_index (pat, i) = program;

    i++;
  }
  pat->len = nb_programs;

  if (data != end - 4) {
    GST_ERROR ("STR");
    g_ptr_array_unref (pat);

    return NULL;
  }

  return (gpointer) pat;
}