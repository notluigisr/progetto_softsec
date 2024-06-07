bool ldb_dn_check_local(struct ldb_module *module, struct ldb_dn *dn)
{
	const struct ldb_map_context *data = map_get_context(module);

	if (!data->local_base_dn) {
		return true;
	}

	return ldb_dn_compare_base(data->local_base_dn, dn) == 0;
}