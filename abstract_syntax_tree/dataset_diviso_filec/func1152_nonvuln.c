acldefault_sql(PG_FUNCTION_ARGS)
{
	char		objtypec = PG_GETARG_CHAR(0);
	Oid			owner = PG_GETARG_OID(1);
	GrantObjectType objtype = 0;

	switch (objtypec)
	{
		case 'c':
			objtype = ACL_OBJECT_COLUMN;
			break;
		case 'r':
			objtype = ACL_OBJECT_RELATION;
			break;
		case 's':
			objtype = ACL_OBJECT_SEQUENCE;
			break;
		case 'd':
			objtype = ACL_OBJECT_DATABASE;
			break;
		case 'f':
			objtype = ACL_OBJECT_FUNCTION;
			break;
		case 'l':
			objtype = ACL_OBJECT_LANGUAGE;
			break;
		case 'L':
			objtype = ACL_OBJECT_LARGEOBJECT;
			break;
		case 'n':
			objtype = ACL_OBJECT_NAMESPACE;
			break;
		case 't':
			objtype = ACL_OBJECT_TABLESPACE;
			break;
		case 'F':
			objtype = ACL_OBJECT_FDW;
			break;
		case 'S':
			objtype = ACL_OBJECT_FOREIGN_SERVER;
			break;
		case 'T':
			objtype = ACL_OBJECT_TYPE;
			break;
		default:
			elog(ERROR, "STR", objtypec);
	}

	PG_RETURN_ACL_P(acldefault(objtype, owner));
}