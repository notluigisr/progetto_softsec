char *ldb_dn_canonical_string(TALLOC_CTX *mem_ctx, struct ldb_dn *dn) {
	return ldb_dn_canonical(mem_ctx, dn, 0);

}