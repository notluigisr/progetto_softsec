system_call_script(thread_master_t *m, int (*func) (thread_t *), void * arg, unsigned long timer, notify_script_t* script)
{
	pid_t pid;

	
	if (log_file_name)
		flush_log_file();

	pid = local_fork();

	if (pid < 0) {
		
		log_message(LOG_INFO, "STR");
		return -1;
	}

	if (pid) {
		
		thread_add_child(m, func, arg, pid, timer);
		return 0;
	}

	
#ifdef _MEM_CHECK_
	skip_mem_dump();
#endif

	system_call(script);

	exit(0); 
}