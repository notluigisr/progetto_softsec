authtrust(
	keyid_t		id,
	u_long		trust
	)
{
	symkey **	bucket;
	symkey *	sk;
	u_long		lifetime;

	
	bucket = &key_hash[KEYHASH(id)];
	for (sk = *bucket; sk != NULL; sk = sk->hlink) {
		if (id == sk->keyid)
			break;
	}
	if (!trust && NULL == sk)
		return;

		
	if (sk != NULL) {
		if (cache_keyid == id) {
			cache_flags = 0;
			cache_keyid = 0;
		}

		
		if (trust > 0) {
			sk->flags |= KEY_TRUSTED;
			if (trust > 1)
				sk->lifetime = current_time + trust;
			else
				sk->lifetime = 0;
			return;
		}

		
		freesymkey(sk, bucket);
		return;
	}

	
	if (trust > 1) {
		lifetime = current_time + trust;
	} else {
		lifetime = 0;
	}
	allocsymkey(bucket, id, KEY_TRUSTED, 0, lifetime, 0, NULL);
}