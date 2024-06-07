serialNumberAndIssuerSerialValidate(
	Syntax *syntax,
	struct berval *in )
{
	int rc;
	struct berval sn, i, i_sn;

	Debug( LDAP_DEBUG_TRACE, "STR",
		in->bv_val );

	rc = serialNumberAndIssuerSerialCheck( in, &sn, &i, &i_sn, NULL );
	if ( rc ) {
		goto done;
	}

	 
	rc = dnValidate( NULL, &i );
	if ( rc ) {
		rc = LDAP_INVALID_SYNTAX;
	}

	if ( in->bv_val[0] == '{' && in->bv_val[in->bv_len-1] == '}' ) {
		slap_sl_free( i.bv_val, NULL );
	}

done:;
	Debug( LDAP_DEBUG_TRACE, "STR",
		in->bv_val, rc );

	return rc;
}