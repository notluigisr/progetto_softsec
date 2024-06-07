R_API RBinJavaCPTypeObj *r_bin_java_get_item_from_cp_item_list(RList *cp_list, ut64 idx) {
	
	RBinJavaCPTypeObj *item = NULL;
	if (cp_list == NULL) {
		return NULL;
	}
	item = (RBinJavaCPTypeObj *) r_list_get_n (cp_list, idx);
	return item;
}