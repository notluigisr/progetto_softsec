lasso_saml20_login_check_assertion_signature(LassoLogin *login,
		LassoSaml2Assertion *assertion)
{
	xmlNode *original_node = NULL;
	LassoSaml2NameID *Issuer = NULL;
	LassoServer *server = NULL;
	LassoProfile *profile = NULL;
	char *remote_provider_id = NULL;
	LassoProvider *remote_provider;
	int rc = 0;

	lasso_bad_param(SAML2_ASSERTION, assertion);

	profile = (LassoProfile*)login;
	lasso_extract_node_or_fail(server, lasso_profile_get_server(profile),
			SERVER, LASSO_PROFILE_ERROR_MISSING_SERVER);

	
	Issuer = assertion->Issuer;
	if (! Issuer || 
			! Issuer->content || 
			(Issuer->Format &&
			 lasso_strisnotequal(Issuer->Format,LASSO_SAML2_NAME_IDENTIFIER_FORMAT_ENTITY)))
		
	{
		rc = LASSO_PROFILE_ERROR_MISSING_ISSUER;
		goto cleanup;
	} else {
		remote_provider_id = Issuer->content;
	}
	remote_provider = lasso_server_get_provider(server, remote_provider_id);
	goto_cleanup_if_fail_with_rc(remote_provider, LASSO_SERVER_ERROR_PROVIDER_NOT_FOUND);

	
	original_node = lasso_node_get_original_xmlnode(LASSO_NODE(assertion));
	goto_cleanup_if_fail_with_rc(original_node, LASSO_PROFILE_ERROR_CANNOT_VERIFY_SIGNATURE);

	rc = profile->signature_status = lasso_provider_verify_saml_signature(remote_provider, original_node, NULL);


			message(G_LOG_LEVEL_WARNING, "STR" \
					"STR", assertion->ID);
cleanup:
	switch (rc) {
		case LASSO_SERVER_ERROR_PROVIDER_NOT_FOUND:
			log_verify_assertion_signature_error("STR");
			break;
		case LASSO_PROFILE_ERROR_MISSING_ISSUER:
			log_verify_assertion_signature_error(
				"STR");
			break;
		case LASSO_PROFILE_ERROR_CANNOT_VERIFY_SIGNATURE:
			log_verify_assertion_signature_error(
				"STR");

		default:
			break;
	}
#undef log_verify_assertion_signature_error
	return rc;
}