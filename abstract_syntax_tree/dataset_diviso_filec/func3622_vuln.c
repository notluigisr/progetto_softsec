recv_password_packet(Port *port)
{
	StringInfoData buf;

	if (PG_PROTOCOL_MAJOR(port->proto) >= 3)
	{
		
		int			mtype;

		mtype = pq_getbyte();
		if (mtype != 'p')
		{
			
			if (mtype != EOF)
				ereport(COMMERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
					errmsg("STR",
						   mtype)));
			return NULL;		
		}
	}
	else
	{
		
		if (pq_peekbyte() == EOF)
			return NULL;		
	}

	initStringInfo(&buf);
	if (pq_getmessage(&buf, 1000))		
	{
		
		pfree(buf.data);
		return NULL;
	}

	
	if (strlen(buf.data) + 1 != buf.len)
		ereport(COMMERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("STR")));

	
	ereport(DEBUG5,
			(errmsg("STR")));

	
	return buf.data;
}