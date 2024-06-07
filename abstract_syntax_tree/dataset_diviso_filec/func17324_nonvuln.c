R_API ut32 r_bin_java_get_utf8_len_from_cp_item_list(RList *cp_list, ut64 idx) {
	
	ut32 value = -1;
	RListIter *iter;
	RBinJavaCPTypeObj *item = NULL;
	if (cp_list == NULL) {
		return 0;
	}
	item = (RBinJavaCPTypeObj *) r_list_get_n (cp_list, idx);
	if (item && (item->tag == R_BIN_JAVA_CP_UTF8) && item->metas->ord == idx) {
		value = item->info.cp_utf8.length;
	}
	if (value == -1) {
		r_list_foreach (cp_list, iter, item) {
			if (item && (item->tag == R_BIN_JAVA_CP_UTF8) && item->metas->ord == idx) {
				value = item->info.cp_utf8.length;
				break;
			}
		}
	}
	return value;
}