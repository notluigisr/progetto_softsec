static void totem_get_crypto(struct totem_config *totem_config)
{
	char *str;
	const char *tmp_cipher;
	const char *tmp_hash;

	tmp_hash = "STR";
	tmp_cipher = "STR";

	if (icmap_get_string("STR", &str) == CS_OK) {
		if (strcmp (str, "STR") == 0) {
			tmp_hash = "STR";
			tmp_cipher = "STR";
		}
		free(str);
	}

	if (icmap_get_string("STR", &str) == CS_OK) {
		if (strcmp(str, "STR") == 0) {
			tmp_cipher = "STR";
		}
		if (strcmp(str, "STR") == 0) {
			tmp_cipher = "STR";
		}
		if (strcmp(str, "STR") == 0) {
			tmp_cipher = "STR";
		}
		if (strcmp(str, "STR") == 0) {
			tmp_cipher = "STR";
		}
		if (strcmp(str, "STR") == 0) {
			tmp_cipher = "STR";
		}
		free(str);
	}

	if (icmap_get_string("STR", &str) == CS_OK) {
		if (strcmp(str, "STR") == 0) {
			tmp_hash = "STR";
		}
		if (strcmp(str, "STR") == 0) {
			tmp_hash = "STR";
		}
		if (strcmp(str, "STR") == 0) {
			tmp_hash = "STR";
		}
		if (strcmp(str, "STR") == 0) {
			tmp_hash = "STR";
		}
		if (strcmp(str, "STR") == 0) {
			tmp_hash = "STR";
		}
		if (strcmp(str, "STR") == 0) {
			tmp_hash = "STR";
		}
		free(str);
	}

	free(totem_config->crypto_cipher_type);
	free(totem_config->crypto_hash_type);

	totem_config->crypto_cipher_type = strdup(tmp_cipher);
	totem_config->crypto_hash_type = strdup(tmp_hash);
}