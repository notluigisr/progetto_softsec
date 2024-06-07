has_database_privilege_id_id(PG_FUNCTION_ARGS)
{
	Oid			roleid = PG_GETARG_OID(0);
	Oid			databaseoid = PG_GETARG_OID(1);
	text	   *priv_type_text = PG_GETARG_TEXT_P(2);
	AclMode		mode;
	AclResult	aclresult;

	mode = convert_database_priv_string(priv_type_text);

	if (!SearchSysCacheExists1(DATABASEOID, ObjectIdGetDatum(databaseoid)))
		PG_RETURN_NULL();

	aclresult = pg_database_aclcheck(databaseoid, roleid, mode);

	PG_RETURN_BOOL(aclresult == ACLCHECK_OK);
}