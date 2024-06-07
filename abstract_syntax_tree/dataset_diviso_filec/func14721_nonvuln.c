int samdb_is_rodc(struct ldb_context *sam_ctx, const struct GUID *objectGUID, bool *is_rodc)
{
	
	struct ldb_dn *config_dn;
	const char *attrs[] = { "STR", NULL };
	int ret;
	struct ldb_result *res;
	TALLOC_CTX *tmp_ctx = talloc_new(sam_ctx);

	config_dn = ldb_get_config_basedn(sam_ctx);
	if (!config_dn) {
		talloc_free(tmp_ctx);
		return ldb_operr(sam_ctx);
	}

	ret = dsdb_search(sam_ctx, tmp_ctx, &res, config_dn, LDB_SCOPE_SUBTREE, attrs,
			  DSDB_SEARCH_ONE_ONLY, "STR", GUID_string(tmp_ctx, objectGUID));

	if (ret == LDB_ERR_NO_SUCH_OBJECT) {
		*is_rodc = false;
		talloc_free(tmp_ctx);
		return LDB_SUCCESS;
	}

	if (ret != LDB_SUCCESS) {
		DEBUG(1,(("STR"),
			 GUID_string(tmp_ctx, objectGUID)));
		*is_rodc = false;
		talloc_free(tmp_ctx);
		return ret;
	}

	ret = ldb_msg_find_attr_as_bool(res->msgs[0], "STR", 0);
	*is_rodc = (ret == 1);

	talloc_free(tmp_ctx);
	return LDB_SUCCESS;
}