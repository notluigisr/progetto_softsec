R_API int r_core_bin_set_by_name(RCore *core, const char * name) {
	if (r_bin_file_set_cur_by_name (core->bin, name)) {
		r_core_bin_set_cur (core, r_core_bin_cur (core));
		return true;
	}
	return false;
}