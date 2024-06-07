StatementCancelHandler(SIGNAL_ARGS)
{
	int			save_errno = errno;

	
	if (!proc_exit_inprogress)
	{
		InterruptPending = true;
		QueryCancelPending = true;

		
		if (ImmediateInterruptOK)
			ProcessInterrupts();
	}

	
	SetLatch(MyLatch);

	errno = save_errno;
}