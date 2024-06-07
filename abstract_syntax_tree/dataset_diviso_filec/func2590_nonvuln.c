R_API char r_bin_java_resolve_cp_idx_tag(RBinJavaObj *BIN_OBJ, int idx) {
	RBinJavaCPTypeObj *item = NULL;
	if (BIN_OBJ && BIN_OBJ->cp_count < 1) {
		
		return R_BIN_JAVA_CP_UNKNOWN;
	}
	item = (RBinJavaCPTypeObj *) r_bin_java_get_item_from_bin_cp_list (BIN_OBJ, idx);
	if (item) {
		return item->tag;
	}
	return R_BIN_JAVA_CP_UNKNOWN;
}