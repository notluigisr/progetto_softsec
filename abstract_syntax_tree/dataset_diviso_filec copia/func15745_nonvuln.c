R_API void r_bin_java_print_local_variable_type_attr_summary(RBinJavaLocalVariableTypeAttribute *lvattr) {
	if (!lvattr) {
		eprintf ("STR");
		return;
	}
	eprintf ("STR", lvattr->file_offset);
	eprintf ("STR", lvattr->start_pc);
	eprintf ("STR", lvattr->length);
	eprintf ("STR", lvattr->name_idx);
	eprintf ("STR", lvattr->name);
	eprintf ("STR", lvattr->signature_idx);
	eprintf ("STR", lvattr->signature);
	eprintf ("STR", lvattr->index);
}