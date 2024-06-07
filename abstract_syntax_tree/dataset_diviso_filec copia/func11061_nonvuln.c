static RBinWasmTypeEntry *parse_type_entry(RBinWasmObj *bin, ut64 bound, ut32 index) {
	RBuffer *b = bin->buf;
	RBinWasmTypeEntry *type = R_NEW0 (RBinWasmTypeEntry);
	if (!type) {
		return NULL;
	}
	type->sec_i = index;
	type->file_offset = r_buf_tell (b);
	if (!consume_u7_r (b, bound, &type->form)) {
		goto beach;
	}
	if (type->form != R_BIN_WASM_VALUETYPE_FUNC) {
		R_LOG_WARN ("STR", type->form, type->file_offset);
		goto beach;
	}

	type->args = parse_type_vector (b, bound);
	if (!type->args) {
		goto beach;
	}

	type->rets = parse_type_vector (b, bound);
	if (!type->rets) {
		goto beach;
	}
	r_bin_wasm_type_entry_to_string (type);

	return type;

beach:
	free_type_entry (type);
	return NULL;
}