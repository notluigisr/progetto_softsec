int PE_(r_bin_pe_is_stripped_local_syms)(RBinPEObj* pe) {
	if (!pe || !pe->nt_headers) {
		return false;
	}
	return HASCHR (PE_IMAGE_FILE_LOCAL_SYMS_STRIPPED);
}