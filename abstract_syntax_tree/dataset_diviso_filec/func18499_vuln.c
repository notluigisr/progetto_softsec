R_API RBinJavaAttrInfo *r_bin_java_source_debug_attr_new(RBinJavaObj *bin, ut8 *buffer, ut64 sz, ut64 buf_offset) {
	ut64 offset = 6;
	RBinJavaAttrInfo *attr = r_bin_java_default_attr_new (bin, buffer, sz, buf_offset);
	if (!attr) {
		return NULL;
	}
	attr->type = R_BIN_JAVA_ATTR_TYPE_SOURCE_DEBUG_EXTENTSION_ATTR;
	if (attr->length == 0) {
		eprintf ("STR");
		attr->info.debug_extensions.debug_extension = NULL;
		return attr;
	} else if ((attr->length + offset) > sz) {
		eprintf ("STR"
			PFMT64d "STR", attr->length, (offset + sz));
	}
	attr->info.debug_extensions.debug_extension = (ut8 *) malloc (attr->length);
	if (attr->info.debug_extensions.debug_extension && (attr->length > (sz - offset))) {
		memcpy (attr->info.debug_extensions.debug_extension, buffer + offset, sz - offset);
	} else if (attr->info.debug_extensions.debug_extension) {
		memcpy (attr->info.debug_extensions.debug_extension, buffer + offset, attr->length);
	} else {
		eprintf ("STR");
	}
	offset += attr->length;
	attr->size = offset;
	return attr;
}