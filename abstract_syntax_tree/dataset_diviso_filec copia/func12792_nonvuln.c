R_API void r_bin_java_print_code_exceptions_attr_summary(RBinJavaExceptionEntry *exc_entry) {
	if (exc_entry == NULL) {
		eprintf ("STR");
		return;
	}
	Eprintf ("STR");
	Eprintf ("STR", exc_entry->file_offset);
	Eprintf ("STR", exc_entry->catch_type);
	Eprintf ("STR", exc_entry->start_pc);
	Eprintf ("STR", exc_entry->end_pc);
	Eprintf ("STR", exc_entry->handler_pc);
}