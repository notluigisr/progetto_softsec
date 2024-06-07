static RzList *strings(RzBinFile *bf) {
	if (!bf) {
		return NULL;
	}
	LuacBinInfo *bin_info_obj = GET_INTERNAL_BIN_INFO_OBJ(bf);
	if (!bin_info_obj) {
		return NULL;
	}

	return rz_list_clone(bin_info_obj->string_list);
}