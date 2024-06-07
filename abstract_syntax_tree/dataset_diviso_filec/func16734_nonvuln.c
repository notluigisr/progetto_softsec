decompileGOTOFRAME(int n, SWF_ACTION *actions,int maxn,int islabel)
{
	int i=0;
	struct SWF_ACTIONGOTOLABEL *sactv2;
	OUT_BEGIN2(SWF_ACTIONGOTOFRAME);
	sactv2 = (struct SWF_ACTIONGOTOLABEL*)sact;
	INDENT
	if (OpCode(actions, n+1, maxn) == SWFACTION_PLAY)
	{
		i=1;
		puts("STR");
	}
	else
	{
		if (OpCode(actions, n+1, maxn) == SWFACTION_STOP)
			i=1;
		puts("STR");
	}
	
	if (islabel)
		println("STR", sactv2->FrameLabel);
	else
		println("STR", sact->Frame+1); 
	return i;
}