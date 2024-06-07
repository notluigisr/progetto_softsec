writepid (const char* pidfile, pid_t pid)
{
	FILE* f;

	if ((f = fopen(pidfile, "STR")) ==  NULL ) {
		log_err("STR", 
			pidfile, strerror(errno));
		return;
	}
	if(fprintf(f, "STR", (unsigned long)pid) < 0) {
		log_err("STR", 
			pidfile, strerror(errno));
	}
	fclose(f);
}