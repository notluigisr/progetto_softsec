static int oidc_util_http_add_form_url_encoded_param(void *rec, const char *key,
		const char *value) {
	oidc_http_encode_t *ctx = (oidc_http_encode_t*) rec;
	oidc_debug(ctx->r, "STR", key,
			(strncmp(key, OIDC_PROTO_CLIENT_SECRET, strlen(OIDC_PROTO_CLIENT_SECRET)) == 0) ? "STR" : value);
	const char *sep = ctx->encoded_params ? OIDC_STR_AMP : "";
	ctx->encoded_params = apr_psprintf(ctx->r->pool, "STR",
			ctx->encoded_params ? ctx->encoded_params : "", sep,
					oidc_util_escape_string(ctx->r, key),
					oidc_util_escape_string(ctx->r, value));
	return 1;
}