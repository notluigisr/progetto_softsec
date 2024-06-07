gpk_set_filekey(const u8 *key, const u8 *challenge,
		const u8 *r_rn, u8 *kats)
{
	int			r = SC_SUCCESS, outl;
	EVP_CIPHER_CTX		* ctx = NULL;
	u8                      out[16];

	memcpy(out, key+8, 8);
	memcpy(out+8, key, 8);

	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL)
		return SC_ERROR_INTERNAL;

	EVP_EncryptInit_ex(ctx, EVP_des_ede(), NULL, key, NULL);
	if (!EVP_EncryptUpdate(ctx, kats, &outl, r_rn+4, 8))
		r = SC_ERROR_INTERNAL;

	if (!EVP_CIPHER_CTX_cleanup(ctx))
		r = SC_ERROR_INTERNAL;
	if (r == SC_SUCCESS) {
		EVP_CIPHER_CTX_init(ctx);
		EVP_EncryptInit_ex(ctx, EVP_des_ede(), NULL, out, NULL);
		if (!EVP_EncryptUpdate(ctx, kats+8, &outl, r_rn+4, 8))
			r = SC_ERROR_INTERNAL;
	if (!EVP_CIPHER_CTX_cleanup(ctx))
		r = SC_ERROR_INTERNAL;
	}
	memset(out, 0, sizeof(out));

	
	if (r == SC_SUCCESS) {
		EVP_CIPHER_CTX_init(ctx);
		EVP_EncryptInit_ex(ctx, EVP_des_ede(), NULL, kats, NULL);
		if (!EVP_EncryptUpdate(ctx, out, &outl, challenge, 8))
			r = SC_ERROR_INTERNAL;
		if (memcmp(r_rn, out+4, 4) != 0)
			r = SC_ERROR_INVALID_ARGUMENTS;
	}

	if (ctx)
	    EVP_CIPHER_CTX_free(ctx);

	sc_mem_clear(out, sizeof(out));
	return r;
}