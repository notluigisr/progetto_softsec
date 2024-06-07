HaveNFreeProcs(int n)
{
	PGPROC	   *proc;

	
	volatile PROC_HDR *procglobal = ProcGlobal;

	SpinLockAcquire(ProcStructLock);

	proc = procglobal->freeProcs;

	while (n > 0 && proc != NULL)
	{
		proc = (PGPROC *) proc->links.next;
		n--;
	}

	SpinLockRelease(ProcStructLock);

	return (n <= 0);
}