RI_FKey_pk_upd_check_required(Trigger *trigger, Relation pk_rel,
							  HeapTuple old_row, HeapTuple new_row)
{
	const RI_ConstraintInfo *riinfo;

	
	riinfo = ri_FetchConstraintInfo(trigger, pk_rel, true);

	switch (riinfo->confmatchtype)
	{
		case FKCONSTR_MATCH_SIMPLE:
		case FKCONSTR_MATCH_FULL:

			
			if (ri_NullCheck(old_row, riinfo, true) != RI_KEYS_NONE_NULL)
				return false;

			
			if (ri_KeysEqual(pk_rel, old_row, new_row, riinfo, true))
				return false;

			
			return true;

			
		case FKCONSTR_MATCH_PARTIAL:
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("STR")));
			break;

		default:
			elog(ERROR, "STR",
				 riinfo->confmatchtype);
			break;
	}

	
	return false;
}