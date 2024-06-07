R_API ut8 *r_bin_java_get_attr_buf(RBinJavaObj *bin, ut64 sz, const ut64 offset, const ut8 *buf, const ut64 len) {
	ut8 *attr_buf = NULL;
	int pending = len - offset;
	const ut8 *a_buf = offset + buf;
	attr_buf = (ut8 *) calloc (pending + 1, 1);
	if (!attr_buf) {
		eprintf ("STR"PFMT64x
			"STR", sz);
		return attr_buf;
	}
	memcpy (attr_buf, a_buf, pending); 
	return attr_buf;
}