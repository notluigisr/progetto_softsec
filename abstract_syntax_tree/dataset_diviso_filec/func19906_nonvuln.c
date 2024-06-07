getIdentitySequence(Oid relid, AttrNumber attnum, bool missing_ok)
{
	List	   *seqlist = getOwnedSequences_internal(relid, attnum, DEPENDENCY_INTERNAL);

	if (list_length(seqlist) > 1)
		elog(ERROR, "STR");
	else if (list_length(seqlist) < 1)
	{
		if (missing_ok)
			return InvalidOid;
		else
			elog(ERROR, "STR");
	}

	return linitial_oid(seqlist);
}