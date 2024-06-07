R_API void r_bin_java_print_annotation_default_attr_summary(RBinJavaAttrInfo *attr) {
	if (attr && attr->type == R_BIN_JAVA_ATTR_TYPE_ANNOTATION_DEFAULT_ATTR) {
		eprintf ("STR");
		eprintf ("STR", attr->file_offset);
		eprintf ("STR", attr->name_idx, attr->name);
		eprintf ("STR", attr->length);
		r_bin_java_print_element_value_summary ((attr->info.annotation_default_attr.default_value));
	} else {
		
	}
}