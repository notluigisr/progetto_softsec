ATExecAddIndex(AlteredTableInfo *tab, Relation rel,
			   IndexStmt *stmt, bool is_rebuild, LOCKMODE lockmode)
{
	bool		check_rights;
	bool		skip_build;
	bool		quiet;
	Oid			new_index;

	Assert(IsA(stmt, IndexStmt));
	Assert(!stmt->concurrent);

	
	check_rights = !is_rebuild;
	
	skip_build = tab->rewrite || OidIsValid(stmt->oldNode);
	
	quiet = is_rebuild;

	

	new_index = DefineIndex(stmt,
							InvalidOid, 
							true,		
							check_rights,
							skip_build,
							quiet);

	
	if (OidIsValid(stmt->oldNode))
	{
		Relation	irel = index_open(new_index, NoLock);

		RelationPreserveStorage(irel->rd_node, true);
		index_close(irel, NoLock);
	}
}