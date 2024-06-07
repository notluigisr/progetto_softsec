fmgr_c_validator(PG_FUNCTION_ARGS)
{
	Oid			funcoid = PG_GETARG_OID(0);
	void	   *libraryhandle;
	HeapTuple	tuple;
	bool		isnull;
	Datum		tmp;
	char	   *prosrc;
	char	   *probin;

	

	tuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcoid));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "STR", funcoid);

	tmp = SysCacheGetAttr(PROCOID, tuple, Anum_pg_proc_prosrc, &isnull);
	if (isnull)
		elog(ERROR, "STR", funcoid);
	prosrc = TextDatumGetCString(tmp);

	tmp = SysCacheGetAttr(PROCOID, tuple, Anum_pg_proc_probin, &isnull);
	if (isnull)
		elog(ERROR, "STR", funcoid);
	probin = TextDatumGetCString(tmp);

	(void) load_external_function(probin, prosrc, true, &libraryhandle);
	(void) fetch_finfo_record(libraryhandle, prosrc);

	ReleaseSysCache(tuple);

	PG_RETURN_VOID();
}