DropOwnedObjects(DropOwnedStmt *stmt)
{
	List	   *role_ids = roleNamesToIds(stmt->roles);
	ListCell   *cell;

	
	foreach(cell, role_ids)
	{
		Oid			roleid = lfirst_oid(cell);

		if (!has_privs_of_role(GetUserId(), roleid))
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("STR")));
	}

	
	shdepDropOwned(role_ids, stmt->behavior);
}