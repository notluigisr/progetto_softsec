ri_ReportViolation(const RI_ConstraintInfo *riinfo,
				   Relation pk_rel, Relation fk_rel,
				   HeapTuple violator, TupleDesc tupdesc,
				   int queryno, bool spi_err)
{
	StringInfoData key_names;
	StringInfoData key_values;
	bool		onfk;
	const int16 *attnums;
	int			idx;

	if (spi_err)
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("STR",
						RelationGetRelationName(pk_rel),
						NameStr(riinfo->conname),
						RelationGetRelationName(fk_rel)),
				 errhint("STR")));

	
	onfk = (queryno == RI_PLAN_CHECK_LOOKUPPK);
	if (onfk)
	{
		attnums = riinfo->fk_attnums;
		if (tupdesc == NULL)
			tupdesc = fk_rel->rd_att;
	}
	else
	{
		attnums = riinfo->pk_attnums;
		if (tupdesc == NULL)
			tupdesc = pk_rel->rd_att;
	}

	
	initStringInfo(&key_names);
	initStringInfo(&key_values);
	for (idx = 0; idx < riinfo->nkeys; idx++)
	{
		int			fnum = attnums[idx];
		char	   *name,
				   *val;

		name = SPI_fname(tupdesc, fnum);
		val = SPI_getvalue(violator, tupdesc, fnum);
		if (!val)
			val = "STR";

		if (idx > 0)
		{
			appendStringInfoString(&key_names, "STR");
			appendStringInfoString(&key_values, "STR");
		}
		appendStringInfoString(&key_names, name);
		appendStringInfoString(&key_values, val);
	}

	if (onfk)
		ereport(ERROR,
				(errcode(ERRCODE_FOREIGN_KEY_VIOLATION),
				 errmsg("STR",
						RelationGetRelationName(fk_rel),
						NameStr(riinfo->conname)),
				 errdetail("STR",
						   key_names.data, key_values.data,
						   RelationGetRelationName(pk_rel)),
				 errtableconstraint(fk_rel, NameStr(riinfo->conname))));
	else
		ereport(ERROR,
				(errcode(ERRCODE_FOREIGN_KEY_VIOLATION),
				 errmsg("STR",
						RelationGetRelationName(pk_rel),
						NameStr(riinfo->conname),
						RelationGetRelationName(fk_rel)),
			errdetail("STR",
					  key_names.data, key_values.data,
					  RelationGetRelationName(fk_rel)),
				 errtableconstraint(fk_rel, NameStr(riinfo->conname))));
}