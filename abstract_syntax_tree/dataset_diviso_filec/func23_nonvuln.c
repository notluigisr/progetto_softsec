R_API bool r_core_bin_delete(RCore *core, ut32 binfile_idx, ut32 binobj_idx) {
	if (binfile_idx == UT32_MAX && binobj_idx == UT32_MAX) {
		return false;
	}
	if (!r_bin_object_delete (core->bin, binfile_idx, binobj_idx)) {
		return false;
	}
	RBinFile *binfile = r_core_bin_cur (core);
	if (binfile) {
		r_io_raise (core->io, binfile->fd);
	}
	core->switch_file_view = 0;
	return binfile && r_core_bin_set_env (core, binfile) && r_core_block_read (core);
}