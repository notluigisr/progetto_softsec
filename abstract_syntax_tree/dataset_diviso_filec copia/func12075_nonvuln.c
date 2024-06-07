static int replmd_start_transaction(struct ldb_module *module)
{
	
	struct replmd_private *replmd_private = talloc_get_type(ldb_module_get_private(module),
								struct replmd_private);
	replmd_txn_cleanup(replmd_private);

	
	while (replmd_private->ncs) {
		struct nc_entry *e = replmd_private->ncs;
		DLIST_REMOVE(replmd_private->ncs, e);
		talloc_free(e);
	}

	replmd_private->originating_updates = false;

	return ldb_next_start_trans(module);
}