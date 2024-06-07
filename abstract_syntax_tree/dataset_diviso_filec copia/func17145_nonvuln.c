R_API void r_bin_java_print_double_cp_summary(RBinJavaCPTypeObj *obj) {
	ut8 *b = NULL;
	if (!obj) {
		eprintf ("STR");
		return;
	}
	b = obj->info.cp_double.bytes.raw;
	Eprintf ("STR", obj->metas->ord);
	Eprintf ("STR", obj->file_offset);
	Eprintf ("STR", b[0], b[1], b[2], b[3]);
	Eprintf ("STR", b[4], b[5], b[6], b[7]);
	Eprintf ("STR", r_bin_java_raw_to_double (obj->info.cp_double.bytes.raw, 0));
}