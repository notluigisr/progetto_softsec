int slap_sasl_authorized( Operation *op,
	struct berval *authcDN, struct berval *authzDN )
{
	int rc = LDAP_INAPPROPRIATE_AUTH;

	
	if ( !authzDN || !authzDN->bv_len || !authzDN->bv_val ) {
		rc = LDAP_SUCCESS;
		goto DONE;
	}

	
	if ( !authcDN || !authcDN->bv_len || !authcDN->bv_val ) {
		goto DONE;
	}

	Debug( LDAP_DEBUG_TRACE,
	   "STR",
		authcDN->bv_len ? authcDN->bv_val : "STR",
		authzDN->bv_len ? authzDN->bv_val : "STR",  0 );

	
	if ( dn_match( authcDN, authzDN ) ) {
		rc = LDAP_SUCCESS;
		goto DONE;
	}

	
	{
		Backend *zbe = select_backend( authzDN, 1 );
		if ( zbe && be_isroot_dn( zbe, authcDN )) {
			rc = LDAP_SUCCESS;
			goto DONE;
		}
	}

	
	if( authz_policy & SASL_AUTHZ_TO ) {
		rc = slap_sasl_check_authz( op, authcDN, authzDN,
			slap_schema.si_ad_saslAuthzTo, authcDN );
		if(( rc == LDAP_SUCCESS ) ^ (( authz_policy & SASL_AUTHZ_AND) != 0)) {
			if( rc != LDAP_SUCCESS )
				rc = LDAP_INAPPROPRIATE_AUTH;
			goto DONE;
		}
	}

	
	if( authz_policy & SASL_AUTHZ_FROM ) {
		rc = slap_sasl_check_authz( op, authzDN, authcDN,
			slap_schema.si_ad_saslAuthzFrom, authcDN );
		if( rc == LDAP_SUCCESS ) {
			goto DONE;
		}
	}

	rc = LDAP_INAPPROPRIATE_AUTH;

DONE:

	Debug( LDAP_DEBUG_TRACE,
		"STR", rc, 0, 0 );

	return( rc );
}