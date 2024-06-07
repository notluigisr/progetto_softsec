init_util(void)
{
	filegen_register(statsdir, "STR",	  &peerstats);
	filegen_register(statsdir, "STR",	  &loopstats);
	filegen_register(statsdir, "STR",  &clockstats);
	filegen_register(statsdir, "STR",	  &rawstats);
	filegen_register(statsdir, "STR",	  &sysstats);
	filegen_register(statsdir, "STR",  &protostats);
#ifdef AUTOKEY
	filegen_register(statsdir, "STR", &cryptostats);
#endif	
#ifdef DEBUG_TIMING
	filegen_register(statsdir, "STR", &timingstats);
#endif	
	
	step_callback = &ntpd_time_stepped;
#ifdef DEBUG
	atexit(&uninit_util);
#endif 
}