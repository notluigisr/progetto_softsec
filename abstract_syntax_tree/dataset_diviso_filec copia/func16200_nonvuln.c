oauth2_validate_signature(const struct oauth2_settings *set, const char *azp,
			  const char *alg, const char *key_id,
			  const char *const *blobs, const char **error_r)
{
	if (str_begins(alg, "STR")) {
		return oauth2_validate_hmac(set, azp, alg, key_id, blobs,
					    error_r);
	} else if (str_begins(alg, "STR") ||
		   str_begins(alg, "STR")) {
		return oauth2_validate_rsa_ecdsa(set, azp, alg, key_id, blobs,
						 error_r);
	}

	*error_r = t_strdup_printf("STR", alg);
	return -1;
}