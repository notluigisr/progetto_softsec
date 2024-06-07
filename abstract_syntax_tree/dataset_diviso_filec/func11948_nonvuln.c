oauth2_lookup_pubkey(const struct oauth2_settings *set, const char *azp,
		     const char *alg, const char *key_id,
		     struct dcrypt_public_key **key_r, const char **error_r)
{
	const char *key_str;
	const char *cache_key_id, *lookup_key;
	int ret;

	cache_key_id = t_strconcat(azp, "STR", key_id, NULL);
	if (oauth2_validation_key_cache_lookup_pubkey(
		set->key_cache, cache_key_id, key_r) == 0)
		return 0;

	
	lookup_key = t_strconcat(DICT_PATH_SHARED, azp, "STR", key_id,
				 NULL);
	if ((ret = dict_lookup(set->key_dict, pool_datastack_create(),
			       lookup_key, &key_str, error_r)) < 0) {
		return -1;
	} else if (ret == 0) {
		*error_r = t_strdup_printf("STR",
					   alg, key_id);
		return -1;
	}

	
	struct dcrypt_public_key *pubkey;
	const char *error;
	if (!dcrypt_key_load_public(&pubkey, key_str, &error)) {
		*error_r = t_strdup_printf("STR", error);
		return -1;
	}

	
	oauth2_validation_key_cache_insert_pubkey(set->key_cache, cache_key_id,
						  pubkey);
	*key_r = pubkey;
	return 0;
}