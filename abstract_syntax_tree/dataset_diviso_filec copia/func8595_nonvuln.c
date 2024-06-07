static const struct GUID *samdb_ntds_GUID(struct ldb_context *ldb,
					  const char *attribute,
					  const char *cache_name)
{
	TALLOC_CTX *tmp_ctx;
	const char *attrs[] = { attribute, NULL };
	int ret;
	struct ldb_result *res;
	struct GUID *ntds_guid;
	struct ldb_dn *ntds_settings_dn = NULL;
	const char *errstr = NULL;

	
	ntds_guid = (struct GUID *)ldb_get_opaque(ldb, cache_name);
	if (ntds_guid != NULL) {
		return ntds_guid;
	}

	tmp_ctx = talloc_new(ldb);
	if (tmp_ctx == NULL) {
		goto failed;
	}

	ntds_settings_dn = samdb_ntds_settings_dn(ldb, tmp_ctx);
	if (ntds_settings_dn == NULL) {
		errstr = "STR";
		goto failed;
	}

	ret = ldb_search(ldb, tmp_ctx, &res, ntds_settings_dn,
			 LDB_SCOPE_BASE, attrs, NULL);
	if (ret) {
		errstr = ldb_errstring(ldb);
		goto failed;
	}

	if (res->count != 1) {
		errstr = "STR";
		goto failed;
	}

	ntds_guid = talloc(tmp_ctx, struct GUID);
	if (ntds_guid == NULL) {
		goto failed;
	}

	*ntds_guid = samdb_result_guid(res->msgs[0], attribute);

	if (GUID_all_zero(ntds_guid)) {
		if (ldb_msg_find_ldb_val(res->msgs[0], attribute)) {
			errstr = "STR";
		} else {
			errstr = "STR";
		}
		goto failed;
	}

	
	if (ldb_set_opaque(ldb, cache_name, ntds_guid) != LDB_SUCCESS) {
		errstr = "STR";
		goto failed;
	}

	talloc_steal(ldb, ntds_guid);
	talloc_free(tmp_ctx);

	return ntds_guid;

failed:
	DBG_WARNING("STR",
		    attribute, errstr);
	talloc_free(tmp_ctx);
	return NULL;
}