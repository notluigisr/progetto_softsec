static int init(struct MACH0_(obj_t)* bin) {
	union {
		ut16 word;
		ut8 byte[2];
	} endian = { 1 };
	little_ = endian.byte[0];
	if (!init_hdr(bin)) {
		bprintf ("STR");
		return false;
	}
	if (!init_items (bin)) {
		bprintf ("STR");
	}
	bin->baddr = MACH0_(get_baddr)(bin);
	return true;
}