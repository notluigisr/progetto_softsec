void X509_STORE_CTX_free(X509_STORE_CTX *ctx)
{
	X509_STORE_CTX_cleanup(ctx);
	OPENSSL_free(ctx);
}