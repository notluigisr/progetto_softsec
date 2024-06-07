size_t tls12_get_psigalgs(SSL *s, const unsigned char **psigs)
	{
	
#ifndef OPENSSL_NO_EC
	switch (tls1_suiteb(s))
		{
	case SSL_CERT_FLAG_SUITEB_128_LOS:
		*psigs = suiteb_sigalgs;
		return sizeof(suiteb_sigalgs);

	case SSL_CERT_FLAG_SUITEB_128_LOS_ONLY:
		*psigs = suiteb_sigalgs;
		return 2;

	case SSL_CERT_FLAG_SUITEB_192_LOS:
		*psigs = suiteb_sigalgs + 2;
		return 2;
		}
#endif
	
	if (s->server && s->cert->client_sigalgs)
		{
		*psigs = s->cert->client_sigalgs;
		return s->cert->client_sigalgslen;
		}
	else if (s->cert->conf_sigalgs)
		{
		*psigs = s->cert->conf_sigalgs;
		return s->cert->conf_sigalgslen;
		}
	else
		{
		*psigs = tls12_sigalgs;
#ifdef OPENSSL_FIPS
		
		if (FIPS_mode())
			return sizeof(tls12_sigalgs) - 2;
		else
#endif
			return sizeof(tls12_sigalgs);
		}
	}