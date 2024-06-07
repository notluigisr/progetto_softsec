SetStartupBufferPinWaitBufId(int bufid)
{
	
	volatile PROC_HDR *procglobal = ProcGlobal;

	procglobal->startupBufferPinWaitBufId = bufid;
}