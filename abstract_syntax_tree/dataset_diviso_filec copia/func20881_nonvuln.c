getconfig(
	int	argc,
	char **	argv
	)
{
	char	line[256];

#ifdef DEBUG
	atexit(free_all_config_trees);
#endif
#ifndef SYS_WINNT
	config_file = CONFIG_FILE;
#else
	temp = CONFIG_FILE;
	if (!ExpandEnvironmentStringsA(temp, config_file_storage,
				       sizeof(config_file_storage))) {
		msyslog(LOG_ERR, "STR");
		exit(1);
	}
	config_file = config_file_storage;

	temp = ALT_CONFIG_FILE;
	if (!ExpandEnvironmentStringsA(temp, alt_config_file_storage,
				       sizeof(alt_config_file_storage))) {
		msyslog(LOG_ERR, "STR");
		exit(1);
	}
	alt_config_file = alt_config_file_storage;
#endif 

	
	snprintf(line, sizeof(line), "STR", Version);
	set_sys_var(line, strlen(line) + 1, RO);

	
	set_tod_using = &ntpd_set_tod_using;

	getCmdOpts(argc, argv);
	init_syntax_tree(&cfgt);
	if (
		!lex_init_stack(FindConfig(config_file), "STR")
#ifdef HAVE_NETINFO
		
		&& check_netinfo && !(config_netinfo = get_netinfo_config())
#endif 
		) {
		msyslog(LOG_INFO, "STR", FindConfig(config_file));
#ifndef SYS_WINNT
		io_open_sockets();

		return;
#else
		

		if (!lex_init_stack(FindConfig(alt_config_file), "STR"))  {
			
			msyslog(LOG_INFO, "STR", FindConfig(alt_config_file));
			io_open_sockets();

			return;
		}
		cfgt.source.value.s = estrdup(alt_config_file);
#endif	
	} else
		cfgt.source.value.s = estrdup(config_file);


	
#ifdef DEBUG
	yydebug = !!(debug >= 5);
#endif
	yyparse();
	lex_drop_stack();

	DPRINTF(1, ("STR"));

	cfgt.source.attr = CONF_SOURCE_FILE;
	cfgt.timestamp = time(NULL);

	save_and_apply_config_tree(TRUE);

#ifdef HAVE_NETINFO
	if (config_netinfo)
		free_netinfo_config(config_netinfo);
#endif 
}