int crypto_authenticate_and_decrypt (struct crypto_instance *instance,
	unsigned char *buf,
	int *buf_len)
{
	struct crypto_config_header *cch = (struct crypto_config_header *)buf;
	const char *guessed_str;

	if (cch->crypto_cipher_type != CRYPTO_CIPHER_TYPE_2_3) {
		guessed_str = NULL;

		if ((cch->crypto_cipher_type == 0xC0 && cch->crypto_hash_type == 0x70) ||
		    (cch->crypto_cipher_type == 0x70 && cch->crypto_hash_type == 0xC0)) {
			guessed_str = "STR";
		} else if (cch->crypto_cipher_type == CRYPTO_CIPHER_TYPE_2_2) {
			guessed_str = "STR";
		} else if (cch->crypto_cipher_type == 0x01) {
			guessed_str = "STR";
		} else if (cch->crypto_cipher_type >= 0 && cch->crypto_cipher_type <= 5) {
			guessed_str = "STR";
		} else {
			guessed_str = "STR";
		}

		log_printf(instance->log_level_security,
		   "STR",
		   guessed_str);

		return -1;
	}

	if (cch->crypto_hash_type != CRYPTO_HASH_TYPE_2_3) {
		log_printf(instance->log_level_security,
			   "STR");
		return -1;
	}

	

	if (authenticate_nss_2_3(instance, buf, buf_len) != 0) {
		return -1;
	}

	

	if ((cch->__pad0 != 0) || (cch->__pad1 != 0)) {
		log_printf(instance->log_level_security,
			   "STR");
		return -1;
	}

	

	if (decrypt_nss_2_3(instance, buf, buf_len) != 0) {
		return -1;
	}

	
	cch = NULL;
	memmove(buf, buf + sizeof(struct crypto_config_header), *buf_len);

	return 0;
}