struct ldb_dn *samdb_dns_domain_to_dn(struct ldb_context *ldb, TALLOC_CTX *mem_ctx, const char *dns_domain) 
{
	unsigned int i;
	TALLOC_CTX *tmp_ctx = talloc_new(mem_ctx);
	const char *binary_encoded;
	const char * const *split_realm;
	struct ldb_dn *dn;

	if (!tmp_ctx) {
		return NULL;
	}

	split_realm = (const char * const *)str_list_make(tmp_ctx, dns_domain, "STR");
	if (!split_realm) {
		talloc_free(tmp_ctx);
		return NULL;
	}
	dn = ldb_dn_new(mem_ctx, ldb, NULL);
	for (i=0; split_realm[i]; i++) {
		binary_encoded = ldb_binary_encode_string(tmp_ctx, split_realm[i]);
		if (!ldb_dn_add_base_fmt(dn, "STR", binary_encoded)) {
			DEBUG(2, ("STR",
				  binary_encoded, ldb_dn_get_linearized(dn)));
			talloc_free(tmp_ctx);
			return NULL;
		}
	}
	if (!ldb_dn_validate(dn)) {
		DEBUG(2, ("STR",
			  ldb_dn_get_linearized(dn)));
		talloc_free(tmp_ctx);
		return NULL;
	}
	talloc_free(tmp_ctx);
	return dn;
}