int dsdb_load_partition_usn(struct ldb_context *ldb, struct ldb_dn *dn,
				uint64_t *uSN, uint64_t *urgent_uSN)
{
	struct ldb_request *req;
	int ret;
	TALLOC_CTX *tmp_ctx = talloc_new(ldb);
	struct dsdb_control_current_partition *p_ctrl;
	struct ldb_result *res;

	res = talloc_zero(tmp_ctx, struct ldb_result);
	if (!res) {
		talloc_free(tmp_ctx);
		return ldb_oom(ldb);
	}

	ret = ldb_build_search_req(&req, ldb, tmp_ctx,
				   ldb_dn_new(tmp_ctx, ldb, "STR"),
				   LDB_SCOPE_BASE,
				   NULL, NULL,
				   NULL,
				   res, ldb_search_default_callback,
				   NULL);
	if (ret != LDB_SUCCESS) {
		talloc_free(tmp_ctx);
		return ret;
	}

	p_ctrl = talloc(req, struct dsdb_control_current_partition);
	if (p_ctrl == NULL) {
		talloc_free(tmp_ctx);
		return ldb_oom(ldb);
	}
	p_ctrl->version = DSDB_CONTROL_CURRENT_PARTITION_VERSION;
	p_ctrl->dn = dn;
	
	ret = ldb_request_add_control(req,
				      DSDB_CONTROL_CURRENT_PARTITION_OID,
				      false, p_ctrl);
	if (ret != LDB_SUCCESS) {
		talloc_free(tmp_ctx);
		return ret;
	}
	
	
	ret = ldb_request(ldb, req);
	
	if (ret == LDB_SUCCESS) {
		ret = ldb_wait(req->handle, LDB_WAIT_ALL);
	}

	if (ret == LDB_ERR_NO_SUCH_OBJECT || ret == LDB_ERR_INVALID_DN_SYNTAX) {
		
		*uSN = 0;
		talloc_free(tmp_ctx);
		return LDB_SUCCESS;
	}

	if (ret != LDB_SUCCESS) {
		talloc_free(tmp_ctx);
		return ret;
	}

	if (res->count < 1) {
		*uSN = 0;
		if (urgent_uSN) {
			*urgent_uSN = 0;
		}
	} else {
		*uSN = ldb_msg_find_attr_as_uint64(res->msgs[0], "STR", 0);
		if (urgent_uSN) {
			*urgent_uSN = ldb_msg_find_attr_as_uint64(res->msgs[0], "STR", 0);
		}
	}

	talloc_free(tmp_ctx);

	return LDB_SUCCESS;	
}