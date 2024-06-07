auth_resize_hashtable(void)
{
	u_long		totalkeys;
	u_short		hashbits;
	u_short		hash;
	size_t		newalloc;
	symkey *	sk;

	totalkeys = authnumkeys + authnumfreekeys;
	hashbits = auth_log2(totalkeys / 4.0) + 1;
	hashbits = max(4, hashbits);
	hashbits = min(15, hashbits);

	authhashbuckets = 1 << hashbits;
	authhashmask = authhashbuckets - 1;
	newalloc = authhashbuckets * sizeof(key_hash[0]);

	key_hash = erealloc(key_hash, newalloc);
	memset(key_hash, '\0', newalloc);

	ITER_DLIST_BEGIN(key_listhead, sk, llink, symkey)
		hash = KEYHASH(sk->keyid);
		LINK_SLIST(key_hash[hash], sk, hlink);
	ITER_DLIST_END()
}