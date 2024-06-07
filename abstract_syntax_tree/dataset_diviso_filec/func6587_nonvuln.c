logical_read_xlog_page(XLogReaderState *state, XLogRecPtr targetPagePtr, int reqLen,
				XLogRecPtr targetRecPtr, char *cur_page, TimeLineID *pageTLI)
{
	XLogRecPtr	flushptr;
	int			count;

	
	flushptr = WalSndWaitForWal(targetPagePtr + reqLen);

	
	if (targetPagePtr + XLOG_BLCKSZ <= flushptr)
		count = XLOG_BLCKSZ;
	
	else if (targetPagePtr + reqLen > flushptr)
		return -1;
	
	else
		count = flushptr - targetPagePtr;

	
	XLogRead(cur_page, targetPagePtr, XLOG_BLCKSZ);

	return count;
}