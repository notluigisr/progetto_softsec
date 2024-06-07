R_API void r_bin_java_print_element_pair_summary(RBinJavaElementValuePair *ev_pair) {
	if (!ev_pair) {
		eprintf ("STR");
		return;
	}
	Eprintf ("STR");
	Eprintf ("STR", ev_pair->file_offset);
	Eprintf ("STR", ev_pair->element_name_idx);
	Eprintf ("STR", ev_pair->name);
	Eprintf ("STR");
	r_bin_java_print_element_value_summary (ev_pair->value);
}