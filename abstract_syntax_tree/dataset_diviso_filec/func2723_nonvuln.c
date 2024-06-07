static int fit_image_check_hash(const void *fit, int noffset, const void *data,
				size_t size, char **err_msgp)
{
	uint8_t value[FIT_MAX_HASH_LEN];
	int value_len;
	char *algo;
	uint8_t *fit_value;
	int fit_value_len;
	int ignore;

	*err_msgp = NULL;

	if (fit_image_hash_get_algo(fit, noffset, &algo)) {
		*err_msgp = "STR";
		return -1;
	}
	printf("STR", algo);

	if (IMAGE_ENABLE_IGNORE) {
		fit_image_hash_get_ignore(fit, noffset, &ignore);
		if (ignore) {
			printf("STR");
			return 0;
		}
	}

	if (fit_image_hash_get_value(fit, noffset, &fit_value,
				     &fit_value_len)) {
		*err_msgp = "STR";
		return -1;
	}

	if (calculate_hash(data, size, algo, value, &value_len)) {
		*err_msgp = "STR";
		return -1;
	}

	if (value_len != fit_value_len) {
		*err_msgp = "STR";
		return -1;
	} else if (memcmp(value, fit_value, value_len) != 0) {
		*err_msgp = "STR";
		return -1;
	}

	return 0;
}