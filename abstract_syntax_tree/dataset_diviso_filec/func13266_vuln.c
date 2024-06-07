pq_getbyte_if_available(unsigned char *c)
{
	int			r;

	if (PqRecvPointer < PqRecvLength)
	{
		*c = PqRecvBuffer[PqRecvPointer++];
		return 1;
	}

	
	socket_set_nonblocking(true);

	r = secure_read(MyProcPort, c, 1);
	if (r < 0)
	{
		
		if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
			r = 0;
		else
		{
			
			ereport(COMMERROR,
					(errcode_for_socket_access(),
					 errmsg("STR")));
			r = EOF;
		}
	}
	else if (r == 0)
	{
		
		r = EOF;
	}

	return r;
}