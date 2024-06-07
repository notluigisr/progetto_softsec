has_table_privilege_name_name(PG_FUNCTION_ARGS)
{
	Name		rolename = PG_GETARG_NAME(0);
	text	   *tablename = PG_GETARG_TEXT_P(1);
	text	   *priv_type_text = PG_GETARG_TEXT_P(2);
	Oid			roleid;
	Oid			tableoid;
	AclMode		mode;
	AclResult	aclresult;

	roleid = get_role_oid_or_public(NameStr(*rolename));
	tableoid = convert_table_name(tablename);
	mode = convert_table_priv_string(priv_type_text);

	aclresult = pg_class_aclcheck(tableoid, roleid, mode);

	PG_RETURN_BOOL(aclresult == ACLCHECK_OK);
}