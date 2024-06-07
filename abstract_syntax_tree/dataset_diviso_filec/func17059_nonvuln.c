const char* oidc_util_hdr_in_x_forwarded_port_get(const request_rec *r) {
	return oidc_util_hdr_in_get_left_most_only(r,
			OIDC_HTTP_HDR_X_FORWARDED_PORT, OIDC_STR_COMMA OIDC_STR_SPACE);
}