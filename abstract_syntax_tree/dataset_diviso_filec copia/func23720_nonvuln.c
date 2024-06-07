static int map_rename_do_local(struct map_context *ac)
{
	struct ldb_request *local_req;
	struct ldb_context *ldb;
	int ret;

	ldb = ldb_module_get_ctx(ac->module);

	
	if (ac->local_dn == NULL) {
		
		return ldb_next_remote_request(ac->module, ac->remote_req);
	}

	
	ret = ldb_build_rename_req(&local_req, ldb, ac,
				   ac->req->op.rename.olddn,
				   ac->req->op.rename.newdn,
				   ac->req->controls,
				   ac,
				   map_rename_local_callback,
				   ac->req);
	LDB_REQ_SET_LOCATION(local_req);
	if (ret != LDB_SUCCESS) {
		return LDB_ERR_OPERATIONS_ERROR;
	}

	return ldb_next_request(ac->module, local_req);
}