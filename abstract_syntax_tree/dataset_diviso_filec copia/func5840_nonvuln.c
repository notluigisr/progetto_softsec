static int samldb_unique_attr_check(struct samldb_ctx *ac, const char *attr,
				    const char *attr_conflict,
				    struct ldb_dn *base_dn)
{
	struct ldb_context *ldb = ldb_module_get_ctx(ac->module);
	const char * const no_attrs[] = { NULL };
	struct ldb_result *res = NULL;
	const char *str = NULL;
	const char *enc_str = NULL;
	int ret;

	ret = samldb_get_single_valued_attr(ldb, ac, attr, &str);
	if (ret != LDB_SUCCESS) {
		return ret;
	}
	if (str == NULL) {
		
		return LDB_SUCCESS;
	}

	enc_str = ldb_binary_encode_string(ac, str);
	if (enc_str == NULL) {
		return ldb_module_oom(ac->module);
	}

	
	if (attr_conflict != NULL) {
		ret = dsdb_module_search(ac->module, ac, &res,
					 base_dn,
					 LDB_SCOPE_SUBTREE, no_attrs,
					 DSDB_FLAG_NEXT_MODULE, ac->req,
					 "STR",
					 attr, enc_str,
					 attr_conflict, enc_str);
	} else {
		ret = dsdb_module_search(ac->module, ac, &res,
					 base_dn,
					 LDB_SCOPE_SUBTREE, no_attrs,
					 DSDB_FLAG_NEXT_MODULE, ac->req,
					 "STR", attr, enc_str);
	}
	if (ret != LDB_SUCCESS) {
		return ret;
	}
	if (res->count > 1) {
		return ldb_operr(ldb);
	} else if (res->count == 1) {
		if (ldb_dn_compare(res->msgs[0]->dn, ac->msg->dn) != 0) {
			ldb_asprintf_errstring(ldb,
					       "STR",
					       attr, enc_str);
			return LDB_ERR_ENTRY_ALREADY_EXISTS;
		}
	}
	talloc_free(res);

	return LDB_SUCCESS;
}