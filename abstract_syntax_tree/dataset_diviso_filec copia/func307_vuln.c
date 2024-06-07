ExecWithCheckOptions(ResultRelInfo *resultRelInfo,
					 TupleTableSlot *slot, EState *estate)
{
	ExprContext *econtext;
	ListCell   *l1,
			   *l2;

	
	econtext = GetPerTupleExprContext(estate);

	
	econtext->ecxt_scantuple = slot;

	
	forboth(l1, resultRelInfo->ri_WithCheckOptions,
			l2, resultRelInfo->ri_WithCheckOptionExprs)
	{
		WithCheckOption *wco = (WithCheckOption *) lfirst(l1);
		ExprState  *wcoExpr = (ExprState *) lfirst(l2);

		
		if (!ExecQual((List *) wcoExpr, econtext, false))
			ereport(ERROR,
					(errcode(ERRCODE_WITH_CHECK_OPTION_VIOLATION),
				 errmsg("STR",
						wco->viewname),
					 errdetail("STR",
							   ExecBuildSlotValueDescription(slot,
							RelationGetDescr(resultRelInfo->ri_RelationDesc),
															 64))));
	}
}