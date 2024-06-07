fmgr_internal_validator(PG_FUNCTION_ARGS)
{
	Oid			funcoid = PG_GETARG_OID(0);
	HeapTuple	tuple;
	bool		isnull;
	Datum		tmp;
	char	   *prosrc;

	

	tuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcoid));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "STR", funcoid);

	tmp = SysCacheGetAttr(PROCOID, tuple, Anum_pg_proc_prosrc, &isnull);
	if (isnull)
		elog(ERROR, "STR");
	prosrc = TextDatumGetCString(tmp);

	if (fmgr_internal_function(prosrc) == InvalidOid)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("STR",
						prosrc)));

	ReleaseSysCache(tuple);

	PG_RETURN_VOID();
}