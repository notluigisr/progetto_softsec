authzPretty(
	Syntax *syntax,
	struct berval *val,
	struct berval *out,
	void *ctx)
{
	int		rc;

	Debug( LDAP_DEBUG_TRACE, "STR",
		val->bv_val, 0, 0 );

	rc = authzPrettyNormal( val, out, ctx, 0 );

	Debug( LDAP_DEBUG_TRACE, "STR",
		out->bv_val ? out->bv_val : "STR" , rc, 0 );

	return rc;
}