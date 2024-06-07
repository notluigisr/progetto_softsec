static pj_status_t pjsip_auth_verify( const pjsip_authorization_hdr *hdr,
				      const pj_str_t *method,
				      const pjsip_cred_info *cred_info )
{
    if (pj_stricmp(&hdr->scheme, &pjsip_DIGEST_STR) == 0) {
	char digest_buf[PJSIP_MD5STRLEN];
	pj_str_t digest;
	const pjsip_digest_credential *dig = &hdr->credential.digest;

	
	PJ_ASSERT_RETURN(pj_strcmp(&dig->username, &cred_info->username) == 0,
			 PJ_EINVALIDOP);
	PJ_ASSERT_RETURN(pj_strcmp(&dig->realm, &cred_info->realm) == 0,
			 PJ_EINVALIDOP);

	
	digest.ptr = digest_buf;
	digest.slen = PJSIP_MD5STRLEN;

	
	pjsip_auth_create_digest(&digest, 
				 &hdr->credential.digest.nonce,
				 &hdr->credential.digest.nc, 
				 &hdr->credential.digest.cnonce,
				 &hdr->credential.digest.qop,
				 &hdr->credential.digest.uri,
				 &cred_info->realm,
				 cred_info, 
				 method );

	
	return (pj_stricmp(&digest, &hdr->credential.digest.response) == 0) ?
	       PJ_SUCCESS : PJSIP_EAUTHINVALIDDIGEST;

    } else {
	pj_assert(!"STR");
	return PJSIP_EINVALIDAUTHSCHEME;
    }
}