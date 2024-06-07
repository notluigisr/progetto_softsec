die(SIGNAL_ARGS)
{
	int			save_errno = errno;

	
	if (!proc_exit_inprogress)
	{
		InterruptPending = true;
		ProcDiePending = true;

		
		if (ImmediateInterruptOK && InterruptHoldoffCount == 0 &&
			CritSectionCount == 0)
		{
			
			
			InterruptHoldoffCount++;
			LockErrorCleanup(); 
			DisableNotifyInterrupt();
			DisableCatchupInterrupt();
			InterruptHoldoffCount--;
			ProcessInterrupts();
		}
	}

	
	SetLatch(MyLatch);

	errno = save_errno;
}