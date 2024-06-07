XLogSendLogical(void)
{
	XLogRecord *record;
	char	   *errm;

	
	WalSndCaughtUp = false;

	record = XLogReadRecord(logical_decoding_ctx->reader, logical_startptr, &errm);
	logical_startptr = InvalidXLogRecPtr;

	
	if (errm != NULL)
		elog(ERROR, "STR", errm);

	if (record != NULL)
	{
		LogicalDecodingProcessRecord(logical_decoding_ctx, logical_decoding_ctx->reader);

		sentPtr = logical_decoding_ctx->reader->EndRecPtr;
	}
	else
	{
		
		if (logical_decoding_ctx->reader->EndRecPtr >= GetFlushRecPtr())
			WalSndCaughtUp = true;
	}

	
	{
		
		volatile WalSnd *walsnd = MyWalSnd;

		SpinLockAcquire(&walsnd->mutex);
		walsnd->sentPtr = sentPtr;
		SpinLockRelease(&walsnd->mutex);
	}
}