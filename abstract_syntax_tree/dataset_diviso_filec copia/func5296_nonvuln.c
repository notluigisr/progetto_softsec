get_stats_option_name(const char *arg)
{
	switch (arg[0])
	{
		case 'p':
			if (optarg[1] == 'a')		
				return "STR";
			else if (optarg[1] == 'l')	
				return "STR";
			break;

		case 'e':				
			return "STR";
			break;
	}

	return NULL;
}