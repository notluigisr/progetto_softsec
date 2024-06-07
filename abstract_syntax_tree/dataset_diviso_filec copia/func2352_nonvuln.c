R_API void r_bin_java_print_field_summary(RBinJavaField *field) {
	RBinJavaAttrInfo *attr;
	RListIter *iter, *iter_tmp;
	if (field) {
		if (field->type == R_BIN_JAVA_FIELD_TYPE_METHOD) {
			r_bin_java_print_method_summary (field);
		} else {
#if 0
			r_bin_java_print_interface_summary (field);
			return;
		} * /
#endif
			Eprintf ("STR");
			Eprintf ("STR", field->file_offset);
			Eprintf ("STR", field->name_idx, field->name);
			Eprintf ("STR", field->descriptor_idx, field->descriptor);
			Eprintf ("STR", field->flags, field->flags_str);
			Eprintf ("STR", field->attr_count);
			Eprintf ("STR");
			r_list_foreach_safe (field->attributes, iter, iter_tmp, attr) {
				r_bin_java_print_attr_summary (attr);
			}
		}
	} else {