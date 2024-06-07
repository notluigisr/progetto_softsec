static int check_submodule_url(const char *url)
{
	const char *curl_url;

	if (looks_like_command_line_option(url))
		return -1;

	if (submodule_url_is_relative(url)) {
		
		char *decoded = url_decode(url);
		int has_nl = !!strchr(decoded, '\n');
		free(decoded);
		if (has_nl)
			return -1;
	}

	else if (url_to_curl_url(url, &curl_url)) {
		struct credential c = CREDENTIAL_INIT;
		int ret = credential_from_url_gently(&c, curl_url, 1);
		credential_clear(&c);
		return ret;
	}

	return 0;
}