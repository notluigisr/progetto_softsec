AlterForeignServerOwner_internal(Relation rel, HeapTuple tup, Oid newOwnerId)
{
	Form_pg_foreign_server form;
	Datum		repl_val[Natts_pg_foreign_server];
	bool		repl_null[Natts_pg_foreign_server];
	bool		repl_repl[Natts_pg_foreign_server];
	Acl		   *newAcl;
	Datum		aclDatum;
	bool		isNull;

	form = (Form_pg_foreign_server) GETSTRUCT(tup);

	if (form->srvowner != newOwnerId)
	{
		
		if (!superuser())
		{
			Oid			srvId;
			AclResult	aclresult;

			srvId = HeapTupleGetOid(tup);

			
			if (!pg_foreign_server_ownercheck(srvId, GetUserId()))
				aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_FOREIGN_SERVER,
							   NameStr(form->srvname));

			
			check_is_member_of_role(GetUserId(), newOwnerId);

			
			aclresult = pg_foreign_data_wrapper_aclcheck(form->srvfdw, newOwnerId, ACL_USAGE);
			if (aclresult != ACLCHECK_OK)
			{
				ForeignDataWrapper *fdw = GetForeignDataWrapper(form->srvfdw);

				aclcheck_error(aclresult, OBJECT_FDW, fdw->fdwname);
			}
		}

		memset(repl_null, false, sizeof(repl_null));
		memset(repl_repl, false, sizeof(repl_repl));

		repl_repl[Anum_pg_foreign_server_srvowner - 1] = true;
		repl_val[Anum_pg_foreign_server_srvowner - 1] = ObjectIdGetDatum(newOwnerId);

		aclDatum = heap_getattr(tup,
								Anum_pg_foreign_server_srvacl,
								RelationGetDescr(rel),
								&isNull);
		
		if (!isNull)
		{
			newAcl = aclnewowner(DatumGetAclP(aclDatum),
								 form->srvowner, newOwnerId);
			repl_repl[Anum_pg_foreign_server_srvacl - 1] = true;
			repl_val[Anum_pg_foreign_server_srvacl - 1] = PointerGetDatum(newAcl);
		}

		tup = heap_modify_tuple(tup, RelationGetDescr(rel), repl_val, repl_null,
								repl_repl);

		CatalogTupleUpdate(rel, &tup->t_self, tup);

		
		changeDependencyOnOwner(ForeignServerRelationId, HeapTupleGetOid(tup),
								newOwnerId);
	}

	InvokeObjectPostAlterHook(ForeignServerRelationId,
							  HeapTupleGetOid(tup), 0);
}