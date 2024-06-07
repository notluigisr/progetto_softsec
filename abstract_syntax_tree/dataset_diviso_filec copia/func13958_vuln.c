pq_getbyte(void)
{
	while (PqRecvPointer >= PqRecvLength)
	{
		if (pq_recvbuf())		
			return EOF;			
	}
	return (unsigned char) PqRecvBuffer[PqRecvPointer++];
}