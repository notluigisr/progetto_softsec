MD5auth_setkey(
	keyid_t keyno,
	int	keytype,
	const u_char *key,
	size_t len
	)
{
	symkey *	sk;
	symkey **	bucket;
	u_char *	secret;
	size_t		secretsize;
	
	DEBUG_ENSURE(keytype <= USHRT_MAX);
	DEBUG_ENSURE(len < 4 * 1024);
	
	bucket = &key_hash[KEYHASH(keyno)];
	for (sk = *bucket; sk != NULL; sk = sk->hlink) {
		if (keyno == sk->keyid) {
			
			if (NULL != sk->secret) {
				memset(sk->secret, 0, sk->secretsize);
				free(sk->secret);
			}
			sk->secret = emalloc(len);
			sk->type = (u_short)keytype;
			secretsize = len;
			sk->secretsize = (u_short)secretsize;
#ifndef DISABLE_BUG1243_FIX
			memcpy(sk->secret, key, secretsize);
#else
			
			strncpy((char *)sk->secret, (const char *)key,
				secretsize);
#endif
			if (cache_keyid == keyno) {
				cache_flags = 0;
				cache_keyid = 0;
			}
			return;
		}
	}

	
	secretsize = len;
	secret = emalloc(secretsize);
#ifndef DISABLE_BUG1243_FIX
	memcpy(secret, key, secretsize);
#else
	
	strncpy((char *)secret, (const char *)key, secretsize);
#endif
	allocsymkey(bucket, keyno, 0, (u_short)keytype, 0,
		    (u_short)secretsize, secret);
#ifdef DEBUG
	if (debug >= 4) {
		size_t	j;

		printf("STR", (int)keyno,
		    keytype, (int)secretsize);
		for (j = 0; j < secretsize; j++)
			printf("STR", secret[j]);
		printf("STR");
	}	
#endif
}