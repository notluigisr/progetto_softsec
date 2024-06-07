void (*CRYPTO_get_locking_callback(void))(int mode,int type,const char *file,
		int line)
	{
	return(locking_callback);
	}