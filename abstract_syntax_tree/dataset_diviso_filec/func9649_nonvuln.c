SSL_CIPHER *ssl2_get_cipher_by_char(const unsigned char *p)
	{
	SSL_CIPHER c,*cp;
	unsigned long id;

	id=0x02000000L|((unsigned long)p[0]<<16L)|
		((unsigned long)p[1]<<8L)|(unsigned long)p[2];
	c.id=id;
	cp = (SSL_CIPHER *)OBJ_bsearch((char *)&c,
		(char *)ssl2_ciphers,
		SSL2_NUM_CIPHERS,sizeof(SSL_CIPHER),
		FP_ICC ssl_cipher_id_cmp);
	if ((cp == NULL) || (cp->valid == 0))
		return NULL;
	else
		return cp;
	}