static int oidc_session_redirect_parent_window_to_logout(request_rec *r,
		oidc_cfg *c) {

	oidc_debug(r, "STR");

	char *java_script = apr_psprintf(r->pool,
			"STR"
			"STR"
			"STR", oidc_get_redirect_uri(r, c));

	return oidc_util_html_send(r, "STR", java_script, NULL, NULL,
			OK);
}