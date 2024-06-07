R_API RBinJavaAttrInfo *r_bin_java_read_next_attr_from_buffer(ut8 *buffer, st64 sz, st64 buf_offset) {
	RBinJavaAttrInfo *attr = NULL;
	char *name = NULL;
	ut64 offset = 0;
	ut16 name_idx;
	st64 nsz;
	RBinJavaAttrMetas *type_info = NULL;

	if (!buffer || ((int) sz) < 4 || buf_offset < 0) {
		eprintf ("STR", (int) sz);
		return NULL;
	}
	name_idx = R_BIN_JAVA_USHORT (buffer, offset);
	offset += 2;
	nsz = R_BIN_JAVA_UINT (buffer, offset);
	offset += 4;
	name = r_bin_java_get_utf8_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, name_idx);
	if (!name) {
		name = strdup ("STR");
	}
	IFDBG eprintf("STR", name_idx, name);
	type_info = r_bin_java_get_attr_type_by_name (name);
	if (type_info) {
		IFDBG eprintf("STR", type_info->name, name);
		
		if (nsz > sz) {
			free (name);
			return NULL;
		}
		if ((attr = type_info->allocs->new_obj (buffer, nsz, buf_offset))) {
			attr->metas->ord = (R_BIN_JAVA_GLOBAL_BIN->attr_idx++);
		}
	} else {
		eprintf ("STR", name);
	}
	free (name);
	return attr;
}