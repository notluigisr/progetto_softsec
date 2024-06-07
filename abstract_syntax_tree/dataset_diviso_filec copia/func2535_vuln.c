ExecConstraints(ResultRelInfo *resultRelInfo,
				TupleTableSlot *slot, EState *estate)
{
	Relation	rel = resultRelInfo->ri_RelationDesc;
	TupleDesc	tupdesc = RelationGetDescr(rel);
	TupleConstr *constr = tupdesc->constr;

	Assert(constr);

	if (constr->has_not_null)
	{
		int			natts = tupdesc->natts;
		int			attrChk;

		for (attrChk = 1; attrChk <= natts; attrChk++)
		{
			if (tupdesc->attrs[attrChk - 1]->attnotnull &&
				slot_attisnull(slot, attrChk))
				ereport(ERROR,
						(errcode(ERRCODE_NOT_NULL_VIOLATION),
						 errmsg("STR",
							  NameStr(tupdesc->attrs[attrChk - 1]->attname)),
						 errdetail("STR",
								   ExecBuildSlotValueDescription(slot,
																 tupdesc,
																 64)),
						 errtablecol(rel, attrChk)));
		}
	}

	if (constr->num_check > 0)
	{
		const char *failed;

		if ((failed = ExecRelCheck(resultRelInfo, slot, estate)) != NULL)
			ereport(ERROR,
					(errcode(ERRCODE_CHECK_VIOLATION),
					 errmsg("STR",
							RelationGetRelationName(rel), failed),
					 errdetail("STR",
							   ExecBuildSlotValueDescription(slot,
															 tupdesc,
															 64)),
					 errtableconstraint(rel, failed)));
	}
}