R_API void r_bin_java_print_source_code_file_attr_summary(RBinJavaAttrInfo *attr) {
	if (!attr) {
		eprintf ("STR");
		return;
	}
	printf ("STR");
	printf ("STR", attr->file_offset);
	printf ("STR", attr->name_idx, attr->name);
	printf ("STR", attr->length);
	printf ("STR", attr->info.source_file_attr.sourcefile_idx);
}