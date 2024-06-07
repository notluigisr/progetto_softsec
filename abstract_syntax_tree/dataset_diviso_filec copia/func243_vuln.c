apr_byte_t oidc_cache_get(request_rec *r, const char *section, const char *key,
		char **value) {

	oidc_cfg *cfg = ap_get_module_config(r->server->module_config,
			&auth_openidc_module);
	int encrypted = oidc_cfg_cache_encrypt(r);
	apr_byte_t rc = TRUE;
	char *msg = NULL;

	oidc_debug(r, "STR", key, section,
			encrypted, cfg->cache->name);

	
	if (encrypted == 1)
		key = oidc_cache_get_hashed_key(r, cfg->crypto_passphrase, key);

	
	const char *cache_value = NULL;
	if (cfg->cache->get(r, section, key, &cache_value) == FALSE) {
		rc = FALSE;
		goto out;
	}

	
	if (cache_value == NULL)
		goto out;

	
	if (encrypted == 0) {
		*value = apr_pstrdup(r->pool, cache_value);
		goto out;
	}

	rc = (oidc_cache_crypto_decrypt(r, cache_value,
			oidc_cache_hash_passphrase(r, cfg->crypto_passphrase),
			(unsigned char **) value) > 0);

out:
	
	msg = apr_psprintf(r->pool, "STR",
			cfg->cache->name, encrypted ? "STR", key);
	if (rc == TRUE)
		if (*value != NULL)
			oidc_debug(r, "STR",
					*value ? (int )strlen(*value) : 0, msg);
		else
			oidc_debug(r, "STR", msg);
	else
		oidc_warn(r, "STR", msg);

	return rc;
}