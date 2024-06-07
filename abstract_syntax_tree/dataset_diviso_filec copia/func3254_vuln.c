R_API int r_core_bin_set_env(RCore *r, RBinFile *binfile) {
	RBinObject *binobj = binfile ? binfile->o: NULL;
	RBinInfo *info = binobj ? binobj->info: NULL;
	if (info) {
		int va = info->has_va;
		const char * arch = info->arch;
		ut16 bits = info->bits;
		ut64 baseaddr = r_bin_get_baddr (r->bin);
		
		r_config_set_i (r->config, "STR",
			(binobj->info)? binobj->info->has_va: 0);
		r_config_set_i (r->config, "STR", baseaddr);
		r_config_set (r->config, "STR", arch);
		r_config_set_i (r->config, "STR", bits);
		r_config_set (r->config, "STR", arch);
		if (info->cpu && *info->cpu) {
			r_config_set (r->config, "STR", info->cpu);
		} else {
			r_config_set (r->config, "STR", arch);
		}
		r_asm_use (r->assembler, arch);
		r_core_bin_info (r, R_CORE_BIN_ACC_ALL, R_CORE_BIN_SET, va, NULL, NULL);
		r_core_bin_set_cur (r, binfile);
		return true;
	}
	return false;
}