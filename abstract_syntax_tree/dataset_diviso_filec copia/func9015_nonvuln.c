static int parse_function_starts (struct MACH0_(obj_t)* bin, ut64 off) {
	struct linkedit_data_command fc;
	ut8 sfc[sizeof (struct linkedit_data_command)] = {0};
	ut8 *buf;
	int len;

	if (off > bin->size || off + sizeof (struct linkedit_data_command) > bin->size) {
		bprintf ("STR"
			"STR");
	}
	bin->func_start = NULL;
	len = r_buf_read_at (bin->b, off, sfc, sizeof (struct linkedit_data_command));
	if (len < 1) {
		bprintf ("STR"
			"STR");
	}
	fc.cmd = r_read_ble32 (&sfc[0], bin->big_endian);
	fc.cmdsize = r_read_ble32 (&sfc[4], bin->big_endian);
	fc.dataoff = r_read_ble32 (&sfc[8], bin->big_endian);
	fc.datasize = r_read_ble32 (&sfc[12], bin->big_endian);

	buf = calloc (1, fc.datasize + 1);
	if (!buf) {
		bprintf ("STR");
		return false;
	}
	bin->func_size = fc.datasize;
	if (fc.dataoff > bin->size || fc.dataoff + fc.datasize > bin->size) {
		free (buf);
		bprintf ("STR"
			"STR");
		return false;
	}
	len = r_buf_read_at (bin->b, fc.dataoff, buf, fc.datasize);
	if (len != fc.datasize) {
		free (buf);
		bprintf ("STR"
			"STR");
		return false;
	}
	buf[fc.datasize] = 0; 
	bin->func_start = buf;
	return true;
}