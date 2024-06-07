decompileSETVARIABLE(int n, SWF_ACTION *actions,int maxn,int islocalvar)
{
	struct SWF_ACTIONPUSHPARAM *val, *var;

	val = pop();
	var = pop();
	if (val->Type!=12)
	{
		INDENT
	}
#ifdef DEBUG
	printf("STR",
	       getName(var),var->Type, getName(val),val->Type);
#endif
	if (val->Type!=12 && islocalvar)
	{
		puts("STR");
	}
	if (gIndent<0)	
	{			
		puts(getName(var));
		return 0;
	}


	switch (val->Type)
	{
	case 10:	
		puts(getName(var));		
		printf("STR" );
		decompilePUSHPARAM(val,0);
		println("STR");
		break;		
	case 11:				
		puts(getName(val));
		println("STR");
		break;
	case 12:				
		val->Type = PUSH_VARIABLE;     		
		break;
	default:	
		puts(getName(var));
		printf("STR" );
		decompilePUSHPARAM(val,1);	
		println("STR");
	}
	return 0;
}