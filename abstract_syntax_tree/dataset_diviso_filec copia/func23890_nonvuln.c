static int replmd_delete_link_value(struct ldb_module *module,
				    struct replmd_private *replmd_private,
				    TALLOC_CTX *mem_ctx,
				    struct ldb_dn *src_obj_dn,
				    const struct dsdb_schema *schema,
				    const struct dsdb_attribute *attr,
				    uint64_t seq_num,
				    bool is_active,
				    struct GUID *target_guid,
				    struct dsdb_dn *target_dsdb_dn,
				    struct ldb_val *output_val)
{
	struct ldb_context *ldb = ldb_module_get_ctx(module);
	time_t t;
	NTTIME now;
	const struct GUID *invocation_id = NULL;
	int ret;

	t = time(NULL);
	unix_to_nt_time(&now, t);

	invocation_id = samdb_ntds_invocation_id(ldb);
	if (invocation_id == NULL) {
		return LDB_ERR_OPERATIONS_ERROR;
	}

	
	if (is_active) {

		
		ret = replmd_add_backlink(module, replmd_private, schema,
					  src_obj_dn, target_guid, false,
					  attr, NULL);
		if (ret != LDB_SUCCESS) {
			return ret;
		}
	}

	
	ret = replmd_update_la_val(mem_ctx, output_val, target_dsdb_dn,
				   target_dsdb_dn, invocation_id, seq_num,
				   seq_num, now, true);
	return ret;
}