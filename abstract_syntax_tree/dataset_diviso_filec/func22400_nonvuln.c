int PE_(bin_pe_get_claimed_checksum)(RBinPEObj* pe) {
	if (!pe || !pe->optional_header) {
		return 0;
	}
	return pe->optional_header->CheckSum;
}