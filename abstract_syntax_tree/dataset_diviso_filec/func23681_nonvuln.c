has_tablespace_privilege_name_name(PG_FUNCTION_ARGS)
{
	Name		username = PG_GETARG_NAME(0);
	text	   *tablespacename = PG_GETARG_TEXT_P(1);
	text	   *priv_type_text = PG_GETARG_TEXT_P(2);
	Oid			roleid;
	Oid			tablespaceoid;
	AclMode		mode;
	AclResult	aclresult;

	roleid = get_role_oid_or_public(NameStr(*username));
	tablespaceoid = convert_tablespace_name(tablespacename);
	mode = convert_tablespace_priv_string(priv_type_text);

	aclresult = pg_tablespace_aclcheck(tablespaceoid, roleid, mode);

	PG_RETURN_BOOL(aclresult == ACLCHECK_OK);
}