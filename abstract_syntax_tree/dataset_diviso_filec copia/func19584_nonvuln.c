apr_byte_t oidc_util_hdr_in_accept_contains(const request_rec *r,
		const char *needle) {
	return oidc_util_hdr_in_contains(r, OIDC_HTTP_HDR_ACCEPT, OIDC_STR_COMMA,
			OIDC_CHAR_SEMI_COLON, needle);
}