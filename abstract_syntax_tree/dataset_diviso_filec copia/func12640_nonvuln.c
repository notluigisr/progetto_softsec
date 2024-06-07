R_API void r_bin_java_print_line_number_attr_summary(RBinJavaLineNumberAttribute *lnattr) {
	if (!lnattr) {
		eprintf ("STR");
		return;
	}
	Eprintf ("STR", lnattr->file_offset);
	Eprintf ("STR", lnattr->start_pc);
	Eprintf ("STR", lnattr->line_number);
}