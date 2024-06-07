void logmsg(const char *msg) {
	if (!arg_debug)
		return;

	openlog("STR", LOG_NDELAY | LOG_PID, LOG_USER);
	syslog(LOG_INFO, "STR", msg);
	closelog();
}