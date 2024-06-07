int SSL_CTX_use_certificate_ASN1(SSL_CTX *ctx, int len, const unsigned char *d)
	{
	X509 *x;
	int ret;

	x=d2i_X509(NULL,&d,(long)len);
	if (x == NULL)
		{
		SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_ASN1,ERR_R_ASN1_LIB);
		return(0);
		}

	ret=SSL_CTX_use_certificate(ctx,x);
	X509_free(x);
	return(ret);
	}