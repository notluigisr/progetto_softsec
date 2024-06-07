R_API void r_bin_java_print_utf8_cp_summary(RBinJavaCPTypeObj *obj) {
	if (!obj) {
		eprintf ("STR");
		return;
	}
	char *str = convert_string ((const char *) obj->info.cp_utf8.bytes, obj->info.cp_utf8.length);
	eprintf ("STR", obj->metas->ord);
	eprintf ("STR", obj->file_offset);
	eprintf ("STR", obj->info.cp_utf8.length);
	eprintf ("STR", str);
	free (str);
}