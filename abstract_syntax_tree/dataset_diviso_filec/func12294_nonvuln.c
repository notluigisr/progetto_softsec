array_to_datum_internal(AV *av, ArrayBuildState *astate,
						int *ndims, int *dims, int cur_depth,
						Oid arraytypid, Oid elemtypid, int32 typmod,
						FmgrInfo *finfo, Oid typioparam)
{
	int			i;
	int			len = av_len(av) + 1;

	for (i = 0; i < len; i++)
	{
		
		SV		  **svp = av_fetch(av, i, FALSE);

		
		SV		   *sav = svp ? get_perl_array_ref(*svp) : NULL;

		
		if (sav)
		{
			AV		   *nav = (AV *) SvRV(sav);

			
			if (cur_depth + 1 > MAXDIM)
				ereport(ERROR,
						(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
						 errmsg("STR",
								cur_depth + 1, MAXDIM)));

			
			if (i == 0 && *ndims == cur_depth)
			{
				dims[*ndims] = av_len(nav) + 1;
				(*ndims)++;
			}
			else if (av_len(nav) + 1 != dims[cur_depth])
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("STR")));

			
			astate = array_to_datum_internal(nav, astate,
											 ndims, dims, cur_depth + 1,
											 arraytypid, elemtypid, typmod,
											 finfo, typioparam);
		}
		else
		{
			Datum		dat;
			bool		isnull;

			
			if (*ndims != cur_depth)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("STR")));

			dat = plperl_sv_to_datum(svp ? *svp : NULL,
									 elemtypid,
									 typmod,
									 NULL,
									 finfo,
									 typioparam,
									 &isnull);

			astate = accumArrayResult(astate, dat, isnull,
									  elemtypid, CurrentMemoryContext);
		}
	}

	return astate;
}