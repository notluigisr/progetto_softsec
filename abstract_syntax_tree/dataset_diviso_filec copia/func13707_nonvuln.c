DoCopyTo(CopyState cstate)
{
	bool		pipe = (cstate->filename == NULL);
	bool		fe_copy = (pipe && whereToSendOutput == DestRemote);
	uint64		processed;

	PG_TRY();
	{
		if (fe_copy)
			SendCopyBegin(cstate);

		processed = CopyTo(cstate);

		if (fe_copy)
			SendCopyEnd(cstate);
	}
	PG_CATCH();
	{
		
		pq_endcopyout(true);
		PG_RE_THROW();
	}
	PG_END_TRY();

	return processed;
}