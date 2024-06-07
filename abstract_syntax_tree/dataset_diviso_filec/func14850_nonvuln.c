pq_putbytes(const char *s, size_t len)
{
	int			res;

	
	Assert(DoingCopyOut);
	
	if (PqCommBusy)
		return 0;
	PqCommBusy = true;
	res = internal_putbytes(s, len);
	PqCommBusy = false;
	return res;
}