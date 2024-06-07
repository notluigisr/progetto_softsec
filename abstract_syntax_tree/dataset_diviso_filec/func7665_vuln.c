static int samldb_lockout_time(struct samldb_ctx *ac)
{
	struct ldb_context *ldb = ldb_module_get_ctx(ac->module);
	NTTIME lockoutTime;
	struct ldb_message_element *el;
	struct ldb_message *tmp_msg;
	int ret;

	ret = dsdb_get_expected_new_values(ac,
					   ac->msg,
					   "STR",
					   &el,
					   ac->req->operation);
	if (ret != LDB_SUCCESS) {
		return ret;
	}

	if (el == NULL || el->num_values == 0) {
		ldb_asprintf_errstring(ldb,
			"STR",
			W_ERROR_V(WERR_DS_ILLEGAL_MOD_OPERATION));
		return LDB_ERR_UNWILLING_TO_PERFORM;
	}

	
	tmp_msg = ldb_msg_new(ac->msg);
	if (tmp_msg == NULL) {
		return ldb_module_oom(ac->module);
	}
	ret = ldb_msg_add(tmp_msg, el, 0);
	if (ret != LDB_SUCCESS) {
		return ret;
	}
	lockoutTime = ldb_msg_find_attr_as_int64(tmp_msg,
						 "STR",
						 0);
	talloc_free(tmp_msg);

	if (lockoutTime != 0) {
		return LDB_SUCCESS;
	}

	
	ldb_msg_remove_attr(ac->msg, "STR");
	ret = samdb_msg_add_int(ldb, ac->msg, ac->msg,
				"STR", 0);
	if (ret != LDB_SUCCESS) {
		return ret;
	}
	el = ldb_msg_find_element(ac->msg, "STR");
	el->flags = LDB_FLAG_MOD_REPLACE;

	return LDB_SUCCESS;
}