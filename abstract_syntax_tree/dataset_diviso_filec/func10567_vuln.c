int ssl_cipher_list_to_bytes(SSL *s,STACK_OF(SSL_CIPHER) *sk,unsigned char *p,
			     int (*put_cb)(const SSL_CIPHER *, unsigned char *))
	{
	int i,j=0;
	SSL_CIPHER *c;
	unsigned char *q;
#ifndef OPENSSL_NO_KRB5
	int nokrb5 = !kssl_tgt_is_available(s->kssl_ctx);
#endif 

	if (sk == NULL) return(0);
	q=p;

	for (i=0; i<sk_SSL_CIPHER_num(sk); i++)
		{
		c=sk_SSL_CIPHER_value(sk,i);
		
		if ((c->algorithm_ssl & SSL_TLSV1_2) && 
			(TLS1_get_client_version(s) < TLS1_2_VERSION))
			continue;
#ifndef OPENSSL_NO_KRB5
		if (((c->algorithm_mkey & SSL_kKRB5) || (c->algorithm_auth & SSL_aKRB5)) &&
		    nokrb5)
		    continue;
#endif 
#ifndef OPENSSL_NO_PSK
		
		if (((c->algorithm_mkey & SSL_kPSK) || (c->algorithm_auth & SSL_aPSK)) &&
		    s->psk_client_callback == NULL)
			continue;
#endif 
#ifndef OPENSSL_NO_SRP
		if (((c->algorithm_mkey & SSL_kSRP) || (c->algorithm_auth & SSL_aSRP)) &&
		    !(s->srp_ctx.srp_Mask & SSL_kSRP))
		    continue;
#endif 
		j = put_cb ? put_cb(c,p) : ssl_put_cipher_by_char(s,c,p);
		p+=j;
		}
	
	if (p != q && !s->renegotiate)
		{
		static SSL_CIPHER scsv =
			{
			0, NULL, SSL3_CK_SCSV, 0, 0, 0, 0, 0, 0, 0, 0, 0
			};
		j = put_cb ? put_cb(&scsv,p) : ssl_put_cipher_by_char(s,&scsv,p);
		p+=j;
#ifdef OPENSSL_RI_DEBUG
		fprintf(stderr, "STR");
#endif
		}

	return(p-q);
	}