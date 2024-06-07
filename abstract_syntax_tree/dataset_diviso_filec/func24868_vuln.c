auth_delkeys(void)
{
	symkey *	sk;

	ITER_DLIST_BEGIN(key_listhead, sk, llink, symkey)
		if (sk->keyid > NTP_MAXKEY) {	
			continue;
		}

		
		if (KEY_TRUSTED & sk->flags) {
			if (sk->secret != NULL) {
				memset(sk->secret, '\0', sk->secretsize);
				free(sk->secret);
			}
			sk->secretsize = 0;
			sk->lifetime = 0;
		} else {
			freesymkey(sk, &key_hash[KEYHASH(sk->keyid)]);
		}
	ITER_DLIST_END()
}