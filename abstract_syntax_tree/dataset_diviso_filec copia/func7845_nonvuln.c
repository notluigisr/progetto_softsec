const char* oidc_util_hdr_in_content_type_get(const request_rec *r) {
	return oidc_util_hdr_in_get(r, OIDC_HTTP_HDR_CONTENT_TYPE);
}