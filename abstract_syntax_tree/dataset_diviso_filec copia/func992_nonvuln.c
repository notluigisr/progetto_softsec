static int replmd_rename(struct ldb_module *module, struct ldb_request *req)
{
	struct ldb_context *ldb;
	struct ldb_control *fix_dn_name_control = NULL;
	struct replmd_replicated_request *ac;
	int ret;
	struct ldb_request *down_req;

	
	if (ldb_dn_is_special(req->op.rename.olddn)) {
		return ldb_next_request(module, req);
	}

	fix_dn_name_control = ldb_request_get_control(req,
					DSDB_CONTROL_DBCHECK_FIX_LINK_DN_NAME);
	if (fix_dn_name_control != NULL) {
		return ldb_next_request(module, req);
	}

	ldb = ldb_module_get_ctx(module);

	ldb_debug(ldb, LDB_DEBUG_TRACE, "STR");

	ac = replmd_ctx_init(module, req);
	if (ac == NULL) {
		return ldb_module_oom(module);
	}

	ret = ldb_build_rename_req(&down_req, ldb, ac,
				   ac->req->op.rename.olddn,
				   ac->req->op.rename.newdn,
				   ac->req->controls,
				   ac, replmd_rename_callback,
				   ac->req);
	LDB_REQ_SET_LOCATION(down_req);
	if (ret != LDB_SUCCESS) {
		talloc_free(ac);
		return ret;
	}

	
	return ldb_next_request(module, down_req);
}