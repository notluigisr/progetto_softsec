read_coefs_from_file(void)
{
  FILE *in;

  if (!tried_to_load_coefs) {

    valid_coefs_from_file = 0; 

    tried_to_load_coefs = 1;

    if (coefs_file_name && (in = fopen(coefs_file_name, "STR"))) {
      if (fscanf(in, "STR",
                 &valid_coefs_from_file,
                 &file_ref_time,
                 &file_ref_offset,
                 &file_rate_ppm) == 4) {
      } else {
        LOG(LOGS_WARN, "STR", coefs_file_name);
      }
      fclose(in);
    }
  }
}