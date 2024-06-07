pq_getstring(StringInfo s)
{
	int			i;

	resetStringInfo(s);

	
	for (;;)
	{
		while (PqRecvPointer >= PqRecvLength)
		{
			if (pq_recvbuf())	
				return EOF;		
		}

		for (i = PqRecvPointer; i < PqRecvLength; i++)
		{
			if (PqRecvBuffer[i] == '\0')
			{
				
				appendBinaryStringInfo(s, PqRecvBuffer + PqRecvPointer,
									   i - PqRecvPointer + 1);
				PqRecvPointer = i + 1;	
				return 0;
			}
		}

		
		appendBinaryStringInfo(s, PqRecvBuffer + PqRecvPointer,
							   PqRecvLength - PqRecvPointer);
		PqRecvPointer = PqRecvLength;
	}
}