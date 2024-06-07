static int oidc_cache_crypto_encrypt_impl(request_rec *r,
		unsigned char *plaintext, int plaintext_len, const unsigned char *aad,
		int aad_len, unsigned char *key, const unsigned char *iv, int iv_len,
		unsigned char *ciphertext, const unsigned char *tag, int tag_len) {
	EVP_CIPHER_CTX *ctx;

	int len;

	int ciphertext_len;

	
	if (!(ctx = EVP_CIPHER_CTX_new())) {
		oidc_cache_crypto_openssl_error(r, "STR");
		return -1;
	}

	
	if (!EVP_EncryptInit_ex(ctx, OIDC_CACHE_CIPHER, NULL, NULL, NULL)) {
		oidc_cache_crypto_openssl_error(r, "STR");
		return -1;
	}

	
	if (!EVP_CIPHER_CTX_ctrl(ctx, OIDC_CACHE_CRYPTO_SET_IVLEN, iv_len, NULL)) {
		oidc_cache_crypto_openssl_error(r, "STR");
		return -1;
	}

	
	if (!EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv)) {
		oidc_cache_crypto_openssl_error(r, "STR");
		return -1;
	}

	
	if (!EVP_EncryptUpdate(ctx, NULL, &len, aad, aad_len)) {
		oidc_cache_crypto_openssl_error(r, "STR",
				aad_len);
		return -1;
	}

	
	if (!EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
		oidc_cache_crypto_openssl_error(r, "STR");
		return -1;
	}
	ciphertext_len = len;

	
	if (!EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
		oidc_cache_crypto_openssl_error(r, "STR");
		return -1;
	}
	ciphertext_len += len;

	
	if (!EVP_CIPHER_CTX_ctrl(ctx, OIDC_CACHE_CRYPTO_GET_TAG, tag_len,
			(void *) tag)) {
		oidc_cache_crypto_openssl_error(r, "STR");
		return -1;
	}

	
	EVP_CIPHER_CTX_free(ctx);

	return ciphertext_len;
}