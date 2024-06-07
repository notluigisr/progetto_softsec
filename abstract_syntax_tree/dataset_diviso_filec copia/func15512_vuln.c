size_t tls12_get_sig_algs(SSL *s, unsigned char *p)
	{
	TLS_SIGALGS *sptr = s->cert->conf_sigalgs;
	size_t slen;

	

	if (sptr)
		{
		slen = s->cert->conf_sigalgslen;
		if (p)
			{
			size_t i;
			for (i = 0; i < slen; i++, sptr++)
				{
				*p++ = sptr->rhash;
				*p++ = sptr->rsign;
				}
			}
		return slen * 2;
		}
		
	slen = sizeof(tls12_sigalgs);
#ifdef OPENSSL_FIPS
	
	if (FIPS_mode())
		slen -= 2;
#endif
	if (p)
		memcpy(p, tls12_sigalgs, slen);
	return slen;
	}