int SSL_CTX_use_RSAPrivateKey_file(SSL_CTX *ctx, const char *file, int type)
	{
	int j,ret=0;
	BIO *in;
	RSA *rsa=NULL;

	in=BIO_new(BIO_s_file_internal());
	if (in == NULL)
		{
		SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY_FILE,ERR_R_BUF_LIB);
		goto end;
		}

	if (BIO_read_filename(in,file) <= 0)
		{
		SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY_FILE,ERR_R_SYS_LIB);
		goto end;
		}
	if	(type == SSL_FILETYPE_ASN1)
		{
		j=ERR_R_ASN1_LIB;
		rsa=d2i_RSAPrivateKey_bio(in,NULL);
		}
	else if (type == SSL_FILETYPE_PEM)
		{
		j=ERR_R_PEM_LIB;
		rsa=PEM_read_bio_RSAPrivateKey(in,NULL,
			ctx->default_passwd_callback,ctx->default_passwd_callback_userdata);
		}
	else
		{
		SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY_FILE,SSL_R_BAD_SSL_FILETYPE);
		goto end;
		}
	if (rsa == NULL)
		{
		SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY_FILE,j);
		goto end;
		}
	ret=SSL_CTX_use_RSAPrivateKey(ctx,rsa);
	RSA_free(rsa);
end:
	if (in != NULL) BIO_free(in);
	return(ret);
	}