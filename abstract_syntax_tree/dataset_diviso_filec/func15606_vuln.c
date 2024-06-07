static int oidc_cache_crypto_encrypt(request_rec *r, const char *plaintext,
		unsigned char *key, char **result) {
	char *encoded = NULL, *p = NULL, *e_tag = NULL;
	unsigned char *ciphertext = NULL;
	int plaintext_len, ciphertext_len, encoded_len, e_tag_len;
	unsigned char tag[OIDC_CACHE_TAG_LEN];

	
	plaintext_len = strlen(plaintext) + 1;
	ciphertext = apr_pcalloc(r->pool,
			(plaintext_len + EVP_CIPHER_block_size(OIDC_CACHE_CIPHER)));

	ciphertext_len = oidc_cache_crypto_encrypt_impl(r,
			(unsigned char *) plaintext, plaintext_len,
			OIDC_CACHE_CRYPTO_GCM_AAD, sizeof(OIDC_CACHE_CRYPTO_GCM_AAD), key,
			OIDC_CACHE_CRYPTO_GCM_IV, sizeof(OIDC_CACHE_CRYPTO_GCM_IV),
			ciphertext, tag, sizeof(tag));

	
	encoded_len = oidc_base64url_encode(r, &encoded, (const char *) ciphertext,
			ciphertext_len, 1);
	if (encoded_len > 0) {
		p = encoded;

		
		e_tag_len = oidc_base64url_encode(r, &e_tag, (const char *) tag,
				OIDC_CACHE_TAG_LEN, 1);

		
		encoded = apr_pcalloc(r->pool, encoded_len + 1 + e_tag_len + 1);
		memcpy(encoded, p, encoded_len);
		p = encoded + encoded_len;
		*p = OIDC_CHAR_DOT;
		p++;

		
		memcpy(p, e_tag, e_tag_len);
		encoded_len += e_tag_len + 1;

		
		encoded[encoded_len] = '\0';

		*result = encoded;
	}

	return encoded_len;
}