int ssl_prepare_clienthello_tlsext(SSL *s)
	{
#ifndef OPENSSL_NO_EC
	
	int using_ecc = 0;
	int i;
	int algs;
	STACK_OF(SSL_CIPHER) *cipher_stack = SSL_get_ciphers(s);
	for (i = 0; i < sk_SSL_CIPHER_num(cipher_stack); i++)
		{
		algs = (sk_SSL_CIPHER_value(cipher_stack, i))->algorithms;
		if ((algs & SSL_kECDH) || (algs & SSL_kECDHE) || (algs & SSL_aECDSA)) 
			{
			using_ecc = 1;
			break;
			}

		}
	using_ecc = using_ecc && (s->version == TLS1_VERSION);
	if (using_ecc)
		{
		if ((s->tlsext_ecpointformatlist = OPENSSL_malloc(1)) == NULL)
			{
			SSLerr(SSL_F_TLS1_PREPARE_CLIENTHELLO_TLSEXT,ERR_R_MALLOC_FAILURE);
			return -1;
			}
		s->tlsext_ecpointformatlist_length = 1;
		*s->tlsext_ecpointformatlist = TLSEXT_ECPOINTFORMAT_uncompressed;
		}
#endif 
	return 1;
}