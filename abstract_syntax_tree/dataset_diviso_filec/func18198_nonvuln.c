R_API void r_bin_java_print_attr_summary(RBinJavaAttrInfo *attr) {
	if (attr == NULL) {
		eprintf ("STR");
		return;
	}
	((RBinJavaAttrMetas *) attr->metas->type_info)->allocs->print_summary (attr);
}