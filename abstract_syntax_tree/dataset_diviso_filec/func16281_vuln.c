R_API RBinJavaAttrInfo *r_bin_java_rti_annotations_attr_new(RBinJavaObj *bin, ut8 *buffer, ut64 sz, ut64 buf_offset) {
	ut32 i = 0;
	RBinJavaAttrInfo *attr = NULL;
	ut64 offset = 0;
	attr = r_bin_java_default_attr_new (bin, buffer, sz, buf_offset);
	offset += 6;
	if (attr) {
		attr->type = R_BIN_JAVA_ATTR_TYPE_RUNTIME_INVISIBLE_ANNOTATION_ATTR;
		attr->info.annotation_array.num_annotations = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;
		attr->info.annotation_array.annotations = r_list_newf (r_bin_java_annotation_free);
		for (i = 0; i < attr->info.rtv_annotations_attr.num_annotations; i++) {
			if (offset >= sz) {
				break;
			}
			RBinJavaAnnotation *annotation = r_bin_java_annotation_new (buffer + offset, sz - offset, buf_offset + offset);
			if (annotation) {
				offset += annotation->size;
			}
			r_list_append (attr->info.annotation_array.annotations, (void *) annotation);
		}
		attr->size = offset;
	}
	return attr;
}