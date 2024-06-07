static void header(RBinFile *arch) {
	struct r_bin_dex_obj_t *bin = arch->o->bin_obj;
	struct r_bin_t *rbin = arch->rbin;

	rbin->cb_printf ("STR");
	rbin->cb_printf ("STR");
	rbin->cb_printf ("STR", bin->header.checksum);
	rbin->cb_printf ("STR", bin->header.signature[0], bin->header.signature[1], bin->header.signature[18], bin->header.signature[19]);
	rbin->cb_printf ("STR", bin->header.size);
	rbin->cb_printf ("STR", bin->header.header_size);
	rbin->cb_printf ("STR", bin->header.linksection_size);
	rbin->cb_printf ("STR", bin->header.linksection_offset, bin->header.linksection_offset);
	rbin->cb_printf ("STR", bin->header.strings_size);
	rbin->cb_printf ("STR", bin->header.strings_offset, bin->header.strings_offset);
	rbin->cb_printf ("STR", bin->header.types_size);
	rbin->cb_printf ("STR", bin->header.types_offset, bin->header.types_offset);
	rbin->cb_printf ("STR", bin->header.prototypes_size);
	rbin->cb_printf ("STR", bin->header.prototypes_offset, bin->header.prototypes_offset);
	rbin->cb_printf ("STR", bin->header.fields_size);
	rbin->cb_printf ("STR", bin->header.fields_offset, bin->header.fields_offset);
	rbin->cb_printf ("STR", bin->header.method_size);
	rbin->cb_printf ("STR", bin->header.method_offset, bin->header.method_offset);
	rbin->cb_printf ("STR", bin->header.class_size);
	rbin->cb_printf ("STR", bin->header.class_offset, bin->header.class_offset);
	rbin->cb_printf ("STR", bin->header.data_size);
	rbin->cb_printf ("STR", bin->header.data_offset, bin->header.data_offset);

	
	dexdump = true;
	bin->methods_list = NULL;
	dex_loadcode (arch, bin);
	dexdump = false;
}