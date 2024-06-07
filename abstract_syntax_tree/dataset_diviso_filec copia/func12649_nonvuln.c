RemoveUserMapping(DropUserMappingStmt *stmt)
{
	ObjectAddress object;
	Oid			useId;
	Oid			umId;
	ForeignServer *srv;
	RoleSpec   *role = (RoleSpec *) stmt->user;

	if (role->roletype == ROLESPEC_PUBLIC)
		useId = ACL_ID_PUBLIC;
	else
	{
		useId = get_rolespec_oid(stmt->user, stmt->missing_ok);
		if (!OidIsValid(useId))
		{
			
			elog(NOTICE, "STR",
				 role->rolename);
			return InvalidOid;
		}
	}

	srv = GetForeignServerByName(stmt->servername, true);

	if (!srv)
	{
		if (!stmt->missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("STR",
							stmt->servername)));
		
		ereport(NOTICE, (errmsg("STR")));
		return InvalidOid;
	}

	umId = GetSysCacheOid2(USERMAPPINGUSERSERVER,
						   ObjectIdGetDatum(useId),
						   ObjectIdGetDatum(srv->serverid));

	if (!OidIsValid(umId))
	{
		if (!stmt->missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("STR",
							MappingUserName(useId))));

		
		ereport(NOTICE,
				(errmsg("STR",
						MappingUserName(useId))));
		return InvalidOid;
	}

	user_mapping_ddl_aclcheck(useId, srv->serverid, srv->servername);

	
	object.classId = UserMappingRelationId;
	object.objectId = umId;
	object.objectSubId = 0;

	performDeletion(&object, DROP_CASCADE, 0);

	return umId;
}