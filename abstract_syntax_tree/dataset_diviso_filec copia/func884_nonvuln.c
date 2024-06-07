
void napi_hash_add(struct napi_struct *napi)
{
	if (test_bit(NAPI_STATE_NO_BUSY_POLL, &napi->state) ||
	    test_and_set_bit(NAPI_STATE_HASHED, &napi->state))
		return;

	spin_lock(&napi_hash_lock);

	
	do {
		if (unlikely(++napi_gen_id < NR_CPUS + 1))
			napi_gen_id = NR_CPUS + 1;
	} while (napi_by_id(napi_gen_id));
	napi->napi_id = napi_gen_id;

	hlist_add_head_rcu(&napi->napi_hash_node,
			   &napi_hash[napi->napi_id % HASH_SIZE(napi_hash)]);

	spin_unlock(&napi_hash_lock);