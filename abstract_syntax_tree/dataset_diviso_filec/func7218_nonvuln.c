int ldb_msg_add_linearized_dn(struct ldb_message *msg, const char *attr_name,
			      struct ldb_dn *dn)
{
	char *str = ldb_dn_alloc_linearized(msg, dn);

	if (str == NULL) {
		
		return LDB_ERR_OPERATIONS_ERROR;
	}

	return ldb_msg_add_steal_string(msg, attr_name, str);
}