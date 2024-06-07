R_API void r_bin_java_print_rtvp_annotations_attr_summary(RBinJavaAttrInfo *attr) {
	RBinJavaAnnotationsArray *annotation_array = NULL;
	RListIter *iter = NULL, *iter_tmp = NULL;
	if (attr && attr->type == R_BIN_JAVA_ATTR_TYPE_RUNTIME_VISIBLE_PARAMETER_ANNOTATION_ATTR) {
		eprintf ("STR");
		eprintf ("STR", attr->file_offset);
		eprintf ("STR", attr->name_idx, attr->name);
		eprintf ("STR", attr->length);
		eprintf ("STR", attr->info.rtvp_annotations_attr.num_parameters);
		r_list_foreach_safe (attr->info.rtvp_annotations_attr.parameter_annotations, iter, iter_tmp, annotation_array) {
			r_bin_java_print_annotation_array_summary (annotation_array);
		}
	}
}