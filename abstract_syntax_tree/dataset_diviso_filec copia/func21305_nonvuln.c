lasso_saml20_login_validate_request_msg(LassoLogin *login, gboolean authentication_result,
		gboolean is_consent_obtained)
{
	LassoProfile *profile;
	int rc = 0;

	profile = LASSO_PROFILE(login);

	if (authentication_result == FALSE) {
		lasso_saml20_profile_set_response_status_responder(profile,
				LASSO_SAML2_STATUS_CODE_REQUEST_DENIED);
		goto_cleanup_with_rc(LASSO_LOGIN_ERROR_REQUEST_DENIED);
	}

	if (_lasso_login_must_verify_authn_request_signature(profile) && profile->signature_status)
	{
		lasso_saml20_profile_set_response_status_requester(profile,
					LASSO_LIB_STATUS_CODE_INVALID_SIGNATURE);

		if (profile->signature_status == LASSO_DS_ERROR_SIGNATURE_NOT_FOUND) {
			goto_cleanup_with_rc(LASSO_LOGIN_ERROR_UNSIGNED_AUTHN_REQUEST);
		}
		goto_cleanup_with_rc(LASSO_LOGIN_ERROR_INVALID_SIGNATURE);
	}

	rc = lasso_saml20_login_process_federation(login, is_consent_obtained);
	if (rc == LASSO_LOGIN_ERROR_FEDERATION_NOT_FOUND) {
		lasso_saml20_profile_set_response_status_requester(profile,
			LASSO_LIB_STATUS_CODE_FEDERATION_DOES_NOT_EXIST);
		goto cleanup;
	}
	
	if (rc) {
		lasso_saml20_profile_set_response_status_responder(profile,
			LASSO_SAML2_STATUS_CODE_REQUEST_DENIED);
		goto cleanup;
	}

	lasso_saml20_profile_set_response_status_success(profile, NULL);
cleanup:

	return rc;
}