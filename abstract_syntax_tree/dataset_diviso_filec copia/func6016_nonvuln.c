RenameRelationInternal(Oid myrelid, const char *newrelname, bool is_internal)
{
	Relation	targetrelation;
	Relation	relrelation;	
	HeapTuple	reltup;
	Form_pg_class relform;
	Oid			namespaceId;

	
	targetrelation = relation_open(myrelid, AccessExclusiveLock);
	namespaceId = RelationGetNamespace(targetrelation);

	
	relrelation = heap_open(RelationRelationId, RowExclusiveLock);

	reltup = SearchSysCacheCopy1(RELOID, ObjectIdGetDatum(myrelid));
	if (!HeapTupleIsValid(reltup))		
		elog(ERROR, "STR", myrelid);
	relform = (Form_pg_class) GETSTRUCT(reltup);

	if (get_relname_relid(newrelname, namespaceId) != InvalidOid)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_TABLE),
				 errmsg("STR",
						newrelname)));

	
	namestrcpy(&(relform->relname), newrelname);

	simple_heap_update(relrelation, &reltup->t_self, reltup);

	
	CatalogUpdateIndexes(relrelation, reltup);

	InvokeObjectPostAlterHookArg(RelationRelationId, myrelid, 0,
								 InvalidOid, is_internal);

	heap_freetuple(reltup);
	heap_close(relrelation, RowExclusiveLock);

	
	if (OidIsValid(targetrelation->rd_rel->reltype))
		RenameTypeInternal(targetrelation->rd_rel->reltype,
						   newrelname, namespaceId);

	
	if (targetrelation->rd_rel->relkind == RELKIND_INDEX)
	{
		Oid			constraintId = get_index_constraint(myrelid);

		if (OidIsValid(constraintId))
			RenameConstraintById(constraintId, newrelname);
	}

	
	relation_close(targetrelation, NoLock);
}