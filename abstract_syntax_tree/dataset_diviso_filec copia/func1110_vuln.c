authhavekey(
	keyid_t		id
	)
{
	symkey *	sk;

	authkeylookups++;
	if (0 == id || cache_keyid == id) {
		return TRUE;
	}

	
	authkeyuncached++;
	for (sk = key_hash[KEYHASH(id)]; sk != NULL; sk = sk->hlink) {
		if (id == sk->keyid) {
			if (0 == sk->type) {
				authkeynotfound++;
				return FALSE;
			}
			break;
		}
	}

	
	if (NULL == sk) {
		authkeynotfound++;
		return FALSE;
	}
	if (!(KEY_TRUSTED & sk->flags)) {
		authnokey++;
		return FALSE;
	}

	
	cache_keyid = sk->keyid;
	cache_type = sk->type;
	cache_flags = sk->flags;
	cache_secret = sk->secret;
	cache_secretsize = sk->secretsize;

	return TRUE;
}