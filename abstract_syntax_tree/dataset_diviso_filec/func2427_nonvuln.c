config_vars(
	config_tree *ptree
	)
{
	attr_val *curr_var;
	int len;

	curr_var = HEAD_PFIFO(ptree->vars);
	for (; curr_var != NULL; curr_var = curr_var->link) {
		
		switch (curr_var->attr) {

		case T_Broadcastdelay:
			proto_config(PROTO_BROADDELAY, 0, curr_var->value.d, NULL);
			break;
		case T_Tick:
			proto_config(PROTO_ADJ, 0, curr_var->value.d, NULL);
			break;

		case T_Driftfile:
			if ('\0' == curr_var->value.s[0]) {
				stats_drift_file = 0;
				msyslog(LOG_INFO, "STR");
			} else
				stats_config(STATS_FREQ_FILE, curr_var->value.s);
			break;

		case T_Ident:
			sys_ident = curr_var->value.s;
			break;

		case T_WanderThreshold:		
		case T_Nonvolatile:
			wander_threshold = curr_var->value.d;
			break;

		case T_Leapfile:
			stats_config(STATS_LEAP_FILE, curr_var->value.s);
			break;

		case T_Pidfile:
			stats_config(STATS_PID_FILE, curr_var->value.s);
			break;

		case T_Logfile:
			if (-1 == change_logfile(curr_var->value.s, 0))
				msyslog(LOG_ERR,
					"STR",
					curr_var->value.s);
			break;

		case T_Saveconfigdir:
			if (saveconfigdir != NULL)
				free(saveconfigdir);
			len = strlen(curr_var->value.s);
			if (0 == len) {
				saveconfigdir = NULL;
			} else if (DIR_SEP != curr_var->value.s[len - 1]
#ifdef SYS_WINNT	
				   && '/' != curr_var->value.s[len - 1]
#endif
				 ) {
					len++;
					saveconfigdir = emalloc(len + 1);
					snprintf(saveconfigdir, len + 1,
						 "STR",
						 curr_var->value.s,
						 DIR_SEP);
			} else {
					saveconfigdir = estrdup(
					    curr_var->value.s);
			}
			break;

		case T_Automax:
#ifdef AUTOKEY
			sys_automax = curr_var->value.i;
#endif
			break;

		default:
			msyslog(LOG_ERR,
				"STR",
				curr_var->attr);
		}
	}
}