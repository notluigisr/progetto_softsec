pq_peekbyte(void)
{
	while (PqRecvPointer >= PqRecvLength)
	{
		if (pq_recvbuf())		
			return EOF;			
	}
	return (unsigned char) PqRecvBuffer[PqRecvPointer];
}