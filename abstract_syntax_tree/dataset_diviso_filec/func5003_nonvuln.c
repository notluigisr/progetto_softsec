recursive_revoke(Acl *acl,
				 Oid grantee,
				 AclMode revoke_privs,
				 Oid ownerId,
				 DropBehavior behavior)
{
	AclMode		still_has;
	AclItem    *aip;
	int			i,
				num;

	check_acl(acl);

	
	if (grantee == ownerId)
		return acl;

	
	still_has = aclmask(acl, grantee, ownerId,
						ACL_GRANT_OPTION_FOR(revoke_privs),
						ACLMASK_ALL);
	revoke_privs &= ~ACL_OPTION_TO_PRIVS(still_has);
	if (revoke_privs == ACL_NO_RIGHTS)
		return acl;

restart:
	num = ACL_NUM(acl);
	aip = ACL_DAT(acl);
	for (i = 0; i < num; i++)
	{
		if (aip[i].ai_grantor == grantee
			&& (ACLITEM_GET_PRIVS(aip[i]) & revoke_privs) != 0)
		{
			AclItem		mod_acl;
			Acl		   *new_acl;

			if (behavior == DROP_RESTRICT)
				ereport(ERROR,
						(errcode(ERRCODE_DEPENDENT_OBJECTS_STILL_EXIST),
						 errmsg("STR"),
						 errhint("STR")));

			mod_acl.ai_grantor = grantee;
			mod_acl.ai_grantee = aip[i].ai_grantee;
			ACLITEM_SET_PRIVS_GOPTIONS(mod_acl,
									   revoke_privs,
									   revoke_privs);

			new_acl = aclupdate(acl, &mod_acl, ACL_MODECHG_DEL,
								ownerId, behavior);

			pfree(acl);
			acl = new_acl;

			goto restart;
		}
	}

	return acl;
}