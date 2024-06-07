static DexMethodId *dex_method_id_new(RzBuffer *buf, ut64 offset) {
	DexMethodId *method_id = RZ_NEW0(DexMethodId);
	if (!method_id) {
		return NULL;
	}

	read_le16_or_fail(buf, method_id->class_idx, dex_method_id_new_fail);
	read_le16_or_fail(buf, method_id->proto_idx, dex_method_id_new_fail);
	read_le32_or_fail(buf, method_id->name_idx, dex_method_id_new_fail);
	method_id->offset = offset;
	return method_id;

dex_method_id_new_fail:
	free(method_id);
	return NULL;
}