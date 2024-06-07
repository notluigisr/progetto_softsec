static int oidc_request_post_preserved_restore(request_rec *r,
		const char *original_url) {

	oidc_debug(r, "STR", original_url);

	const char *method = "STR";
	const char *script =
			apr_psprintf(r->pool,
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR"
					"STR", method, original_url);

	const char *body = "STR"
			"STR";

	return oidc_util_html_send(r, "STR", script, method, body,
			OK);
}