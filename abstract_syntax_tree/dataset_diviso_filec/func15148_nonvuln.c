int tls1_generate_master_secret(SSL *s, unsigned char *out, unsigned char *p,
	     int len)
	{
	unsigned char buf[SSL3_RANDOM_SIZE*2+TLS_MD_MASTER_SECRET_CONST_SIZE];
	unsigned char buff[SSL_MAX_MASTER_KEY_LENGTH];

#ifdef KSSL_DEBUG
	printf ("STR", (void *)s,out, p,len);
#endif	

	
	memcpy(buf,TLS_MD_MASTER_SECRET_CONST,
		TLS_MD_MASTER_SECRET_CONST_SIZE);
	memcpy(&(buf[TLS_MD_MASTER_SECRET_CONST_SIZE]),
		s->s3->client_random,SSL3_RANDOM_SIZE);
	memcpy(&(buf[SSL3_RANDOM_SIZE+TLS_MD_MASTER_SECRET_CONST_SIZE]),
		s->s3->server_random,SSL3_RANDOM_SIZE);
	tls1_PRF(s->ctx->md5,s->ctx->sha1,
		buf,TLS_MD_MASTER_SECRET_CONST_SIZE+SSL3_RANDOM_SIZE*2,p,len,
		s->session->master_key,buff,sizeof buff);
#ifdef KSSL_DEBUG
	printf ("STR");
#endif	
	return(SSL3_MASTER_SECRET_SIZE);
	}