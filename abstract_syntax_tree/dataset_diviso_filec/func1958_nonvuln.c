static int samldb_rename(struct ldb_module *module, struct ldb_request *req)
{
	struct ldb_context *ldb;
	static const char * const attrs[] = { "STR",
					      "STR", NULL };
	struct ldb_request *search_req;
	struct samldb_ctx *ac;
	int ret;

	if (ldb_dn_is_special(req->op.rename.olddn)) { 
		return ldb_next_request(module, req);
	}

	ldb = ldb_module_get_ctx(module);

	ac = samldb_ctx_init(module, req);
	if (!ac) {
		return ldb_oom(ldb);
	}

	ret = ldb_build_search_req(&search_req, ldb, ac,
				   req->op.rename.olddn,
				   LDB_SCOPE_BASE,
				   "STR",
				   attrs,
				   NULL,
				   ac,
				   samldb_rename_search_base_callback,
				   req);
	LDB_REQ_SET_LOCATION(search_req);
	if (ret != LDB_SUCCESS) {
		return ret;
	}

	ret = ldb_request_add_control(search_req, LDB_CONTROL_SHOW_RECYCLED_OID,
				      true, NULL);
	if (ret != LDB_SUCCESS) {
		return ret;
	}

	return ldb_next_request(ac->module, search_req);
}