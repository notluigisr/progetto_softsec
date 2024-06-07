is_admin_of_role(Oid member, Oid role)
{
	bool		result = false;
	List	   *roles_list;
	ListCell   *l;

	
	if (member == role)
		return true;

	
	if (superuser_arg(member))
		return true;

	
	roles_list = list_make1_oid(member);

	foreach(l, roles_list)
	{
		Oid			memberid = lfirst_oid(l);
		CatCList   *memlist;
		int			i;

		
		memlist = SearchSysCacheList1(AUTHMEMMEMROLE,
									  ObjectIdGetDatum(memberid));
		for (i = 0; i < memlist->n_members; i++)
		{
			HeapTuple	tup = &memlist->members[i]->tuple;
			Oid			otherid = ((Form_pg_auth_members) GETSTRUCT(tup))->roleid;

			if (otherid == role &&
				((Form_pg_auth_members) GETSTRUCT(tup))->admin_option)
			{
				
				result = true;
				break;
			}

			roles_list = list_append_unique_oid(roles_list, otherid);
		}
		ReleaseSysCacheList(memlist);
		if (result)
			break;
	}

	list_free(roles_list);

	return result;
}