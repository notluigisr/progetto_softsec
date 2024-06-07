static const char *txtin_probe_data(const u8 *data, u32 data_size, GF_FilterProbeScore *score)
{
	char *dst = NULL;
	u8 *res;

	res = gf_utf_get_utf8_string_from_bom((char *)data, data_size, &dst);
	if (res) data = res;


		*score = _score;\
		if (dst) gf_free(dst);\
		return _mime; \


	if (!strncmp(data, "STR", 6)) {
		PROBE_OK(GF_FPROBE_SUPPORTED, "STR")
	}
	if (strstr(data, "STR")) {
		PROBE_OK(GF_FPROBE_MAYBE_SUPPORTED, "STR")
	}
	if (!strncmp(data, "STR", 3)) {
		PROBE_OK(GF_FPROBE_MAYBE_SUPPORTED, "STR")
	}

	if ((data[0]=='{') && strstr(data, "STR")) {
		PROBE_OK(GF_FPROBE_MAYBE_SUPPORTED, "STR")

	}
	
	if (!strstr(data, "STR") ) {
		if (dst) gf_free(dst);
		return NULL;
	}

	if (strstr(data, "STR")) {
		PROBE_OK(GF_FPROBE_MAYBE_SUPPORTED, "STR")
	}
	if (strstr(data, "STR")) {
		PROBE_OK(GF_FPROBE_MAYBE_SUPPORTED, "STR")
	}
	if (strstr(data, "STR")) {
		PROBE_OK(GF_FPROBE_MAYBE_SUPPORTED, "STR")
	}

	if (dst) gf_free(dst);
	return NULL;