ATRewriteCatalogs(List **wqueue, LOCKMODE lockmode)
{
	int			pass;
	ListCell   *ltab;

	
	for (pass = 0; pass < AT_NUM_PASSES; pass++)
	{
		
		foreach(ltab, *wqueue)
		{
			AlteredTableInfo *tab = (AlteredTableInfo *) lfirst(ltab);
			List	   *subcmds = tab->subcmds[pass];
			Relation	rel;
			ListCell   *lcmd;

			if (subcmds == NIL)
				continue;

			
			rel = relation_open(tab->relid, NoLock);

			foreach(lcmd, subcmds)
				ATExecCmd(wqueue, tab, rel, (AlterTableCmd *) lfirst(lcmd), lockmode);

			
			if (pass == AT_PASS_ALTER_TYPE)
				ATPostAlterTypeCleanup(wqueue, tab, lockmode);

			relation_close(rel, NoLock);
		}
	}

	
	foreach(ltab, *wqueue)
	{
		AlteredTableInfo *tab = (AlteredTableInfo *) lfirst(ltab);

		if (tab->relkind == RELKIND_RELATION ||
			tab->relkind == RELKIND_MATVIEW)
			AlterTableCreateToastTable(tab->relid, (Datum) 0);
	}
}