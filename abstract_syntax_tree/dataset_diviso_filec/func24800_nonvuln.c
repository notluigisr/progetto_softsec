WalSndShutdown(void)
{
	
	if (whereToSendOutput == DestRemote)
		whereToSendOutput = DestNone;

	proc_exit(0);
	abort();					
}