static inline size_t parse_cipher_suite(uint8_t *cipher_suite_data,
                                        size_t data_len,
                                        uint32_t *iana,
                                        uint8_t *auth_alg,
                                        uint8_t *integrity_alg,
                                        uint8_t *crypt_alg,
                                        enum cipher_suite_ids *cipher_suite_id)
{
	size_t size = 0;
	const char *incomplete = "STR";

	if (*cipher_suite_data == STANDARD_CIPHER_SUITE) {
		struct std_cipher_suite_record_t *record =
			(struct std_cipher_suite_record_t*)cipher_suite_data;

		
		if (data_len < sizeof(*record)) {
			lprintf(LOG_INFO, "STR", incomplete);
			goto out;
		}

		
		*cipher_suite_id = record->cipher_suite_id;
		*auth_alg = CIPHER_ALG_MASK & record->auth_alg;
		*integrity_alg = CIPHER_ALG_MASK & record->integrity_alg;
		*crypt_alg = CIPHER_ALG_MASK & record->crypt_alg;
		size = sizeof(*record);
	} else if (*cipher_suite_data == OEM_CIPHER_SUITE) {
		
		struct oem_cipher_suite_record_t *record =
			(struct oem_cipher_suite_record_t*)cipher_suite_data;
		
		if (data_len < sizeof(*record)) {
			lprintf(LOG_INFO, "STR", incomplete);
			goto out;
		}

		
		*iana = ipmi24toh(record->iana);
		*cipher_suite_id = record->cipher_suite_id;
		*auth_alg = CIPHER_ALG_MASK & record->auth_alg;
		*integrity_alg = CIPHER_ALG_MASK & record->integrity_alg;
		*crypt_alg = CIPHER_ALG_MASK & record->crypt_alg;
		size = sizeof(*record);
	} else {
			lprintf(LOG_INFO, "STR"
			                  "STR", *cipher_suite_data);
	}

out:
	return size;
}