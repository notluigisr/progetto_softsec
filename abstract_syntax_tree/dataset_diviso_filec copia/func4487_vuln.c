pq_getmessage(StringInfo s, int maxlen)
{
	int32		len;

	resetStringInfo(s);

	
	if (pq_getbytes((char *) &len, 4) == EOF)
	{
		ereport(COMMERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("STR")));
		return EOF;
	}

	len = ntohl(len);

	if (len < 4 ||
		(maxlen > 0 && len > maxlen))
	{
		ereport(COMMERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("STR")));
		return EOF;
	}

	len -= 4;					

	if (len > 0)
	{
		
		PG_TRY();
		{
			enlargeStringInfo(s, len);
		}
		PG_CATCH();
		{
			if (pq_discardbytes(len) == EOF)
				ereport(COMMERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("STR")));
			PG_RE_THROW();
		}
		PG_END_TRY();

		
		if (pq_getbytes(s->data, len) == EOF)
		{
			ereport(COMMERROR,
					(errcode(ERRCODE_PROTOCOL_VIOLATION),
					 errmsg("STR")));
			return EOF;
		}
		s->len = len;
		
		s->data[len] = '\0';
	}

	return 0;
}