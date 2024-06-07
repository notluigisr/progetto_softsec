R_API void r_bin_java_rtip_annotations_attr_free(void  *a) {
	RBinJavaAttrInfo *attr = a;
	if (attr) { 
		r_list_free (attr->info.rtip_annotations_attr.parameter_annotations);
		free (attr->metas);
		free (attr->name);
		free (attr);
	}
}