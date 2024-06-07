decompilePUSHPARAM (struct SWF_ACTIONPUSHPARAM *act, int wantstring)
{
	char *t;
	switch( act->Type ) 
	{
	case PUSH_STRING: 
		if( wantstring ) printf ("STR", act->p.String);
		else printf ("STR", act->p.String);
		break;
	case PUSH_FLOAT: 
		printf ("STR", act->p.Float);
		break;
	case PUSH_NULL: 
		printf ("STR" );
		break;
	case PUSH_UNDEF: 
		printf ("STR" );
		break;
	case PUSH_REGISTER: 
		if( regs[act->p.RegisterNumber] ) {
			printf ("STR", getName(act));
		} else {
			printf ("STR", (int)act->p.RegisterNumber);
		}
		break;
	case PUSH_BOOLEAN: 
		printf ("STR");
		break;
	case PUSH_DOUBLE: 
		printf ("STR", act->p.Double);
		break;
	case PUSH_INT: 
		printf ("STR", act->p.Integer);
		break;

	case PUSH_CONSTANT: 
	case PUSH_CONSTANT16: 
		if( wantstring ) t=getString(act);
	  	else t=getName(act);
	  	puts(t);  
	  	free(t);  
	  	break;

#if 0
	  case 8: 
		if (act->p.Constant8 > poolcounter)
		{
		        SWF_warn("STR");
		        break;
		}
		if( wantstring )
  		  printf ("STR", pool[act->p.Constant8]);
		else
  		  printf ("STR", pool[act->p.Constant8]);
		break;
	  case 9: 
		if (act->p.Constant16 > poolcounter)
		{
		        SWF_warn("STR");
		        break;
		}
		if( wantstring )
  		  printf ("STR", pool[act->p.Constant16]);
		else
  		  printf ("STR", pool[act->p.Constant16]);
		break;
#endif
	case 12:
	case 11: 
	case PUSH_VARIABLE: 
		printf ("STR", act->p.String);
		break;
	default: 
		printf ("STR", act->Type);
	}
}