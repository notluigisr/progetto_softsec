int CRYPTO_get_new_lockid(char *name)
	{
	char *str;
	int i;

#if defined(OPENSSL_SYS_WIN32) || defined(OPENSSL_SYS_WIN16)
	
	SSLeay_MSVC5_hack=(double)name[0]*(double)name[1];
#endif

	if ((app_locks == NULL) && ((app_locks=sk_OPENSSL_STRING_new_null()) == NULL))
		{
		CRYPTOerr(CRYPTO_F_CRYPTO_GET_NEW_LOCKID,ERR_R_MALLOC_FAILURE);
		return(0);
		}
	if ((str=BUF_strdup(name)) == NULL)
		{
		CRYPTOerr(CRYPTO_F_CRYPTO_GET_NEW_LOCKID,ERR_R_MALLOC_FAILURE);
		return(0);
		}
	i=sk_OPENSSL_STRING_push(app_locks,str);
	if (!i)
		OPENSSL_free(str);
	else
		i+=CRYPTO_NUM_LOCKS; 
	return(i);
	}