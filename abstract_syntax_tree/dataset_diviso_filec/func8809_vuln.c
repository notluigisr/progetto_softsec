static int samldb_rodc_add(struct samldb_ctx *ac)
{
	struct ldb_context *ldb = ldb_module_get_ctx(ac->module);
	uint32_t krbtgt_number, i_start, i;
	int ret;
	struct ldb_val newpass_utf16;

	
	i_start = generate_random() & 0xFFFF;
	if (i_start == 0) {
		i_start = 1;
	}

	for (i=i_start; i<=0xFFFF; i++) {
		if (samldb_krbtgtnumber_available(ac, i)) {
			krbtgt_number = i;
			goto found;
		}
	}
	for (i=1; i<i_start; i++) {
		if (samldb_krbtgtnumber_available(ac, i)) {
			krbtgt_number = i;
			goto found;
		}
	}

	ldb_asprintf_errstring(ldb,
			       "STR",
			       W_ERROR_V(WERR_NO_SYSTEM_RESOURCES));
	return LDB_ERR_OTHER;

found:
	ret = ldb_msg_add_empty(ac->msg, "STR",
				LDB_FLAG_INTERNAL_DISABLE_VALIDATION, NULL);
	if (ret != LDB_SUCCESS) {
		return ldb_operr(ldb);
	}

	ret = samdb_msg_add_uint(ldb, ac->msg, ac->msg,
				 "STR", krbtgt_number);
	if (ret != LDB_SUCCESS) {
		return ldb_operr(ldb);
	}

	ret = ldb_msg_add_fmt(ac->msg, "STR",
			      krbtgt_number);
	if (ret != LDB_SUCCESS) {
		return ldb_operr(ldb);
	}

	newpass_utf16 = data_blob_talloc_zero(ac->module, 256);
	if (newpass_utf16.data == NULL) {
		return ldb_oom(ldb);
	}
	
	generate_random_buffer(newpass_utf16.data, newpass_utf16.length);
	ret = ldb_msg_add_steal_value(ac->msg, "STR", &newpass_utf16);
	if (ret != LDB_SUCCESS) {
		return ldb_operr(ldb);
	}

	return samldb_next_step(ac);
}