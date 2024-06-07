static int replmd_delete(struct ldb_module *module, struct ldb_request *req)
{
	return replmd_delete_internals(module, req, false);
}