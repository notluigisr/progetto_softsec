static char *oidc_cache_get_hashed_key(request_rec *r, const char *passphrase,
		const char *key) {
	char *input = apr_psprintf(r->pool, "STR", passphrase, key);
	char *output = NULL;
	if (oidc_util_hash_string_and_base64url_encode(r, OIDC_JOSE_ALG_SHA256,
			input, &output) == FALSE) {
		oidc_error(r,
				"STR");
		return NULL;
	}
	return output;
}