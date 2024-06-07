static apr_byte_t oidc_validate_post_logout_url(request_rec *r, const char *url,
		char **err_str, char **err_desc) {
	apr_uri_t uri;
	const char *c_host = NULL;

	if (apr_uri_parse(r->pool, url, &uri) != APR_SUCCESS) {
		*err_str = apr_pstrdup(r->pool, "STR");
		*err_desc = apr_psprintf(r->pool, "STR", url);
		oidc_error(r, "STR", *err_str, *err_desc);
		return FALSE;
	}

	c_host = oidc_get_current_url_host(r);
	if ((uri.hostname != NULL)
			&& ((strstr(c_host, uri.hostname) == NULL)
					|| (strstr(uri.hostname, c_host) == NULL))) {
		*err_str = apr_pstrdup(r->pool, "STR");
		*err_desc =
				apr_psprintf(r->pool,
						"STR",
						apr_uri_unparse(r->pool, &uri, 0), c_host);
		oidc_error(r, "STR", *err_str, *err_desc);
		return FALSE;
	} else if (strstr(url, "STR") != url) {
		*err_str = apr_pstrdup(r->pool, "STR");
		*err_desc =
				apr_psprintf(r->pool,
						"STR",
						url);
		oidc_error(r, "STR", *err_str, *err_desc);
		return FALSE;
	}

	
	if (((strstr(url, "STR") != NULL)) {
		*err_str = apr_pstrdup(r->pool, "STR");
		*err_desc =
				apr_psprintf(r->pool,
						"STR",
						url);
		oidc_error(r, "STR", *err_str, *err_desc);
		return FALSE;
	}

	return TRUE;
}