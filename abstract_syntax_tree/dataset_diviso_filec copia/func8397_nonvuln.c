static void nf_tables_commit_chain_free_rules_old(struct nft_rule_blob *blob)
{
	struct nft_rules_old *old;

	
	old = (void *)blob + sizeof(*blob) + blob->size;
	old->blob = blob;

	call_rcu(&old->h, __nf_tables_commit_chain_free_rules_old);
}