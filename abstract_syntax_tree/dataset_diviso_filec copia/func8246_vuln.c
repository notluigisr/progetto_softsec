prepare_for_client_read(void)
{
	if (DoingCommandRead)
	{
		
		EnableNotifyInterrupt();
		EnableCatchupInterrupt();

		
		ImmediateInterruptOK = true;

		
		CHECK_FOR_INTERRUPTS();
	}
}