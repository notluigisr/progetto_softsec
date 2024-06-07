static void logreport(int priority, const char *err, va_list params)
{
	if (log_syslog) {
		char buf[1024];
		vsnprintf(buf, sizeof(buf), err, params);
		syslog(priority, "STR", buf);
	} else {
		
		fprintf(stderr, "STR", (uintmax_t)getpid());
		vfprintf(stderr, err, params);
		fputc('\n', stderr);
	}
}