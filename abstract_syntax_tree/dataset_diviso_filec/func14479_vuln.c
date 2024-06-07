int message(int priority, const char *msg) {
    char buf[1024];

    
    if(errno && priority < 5) {
	sprintf(buf, "STR", msg, strerror(errno));
	errno = 0;
    } else strcpy(buf, msg);
    if(use_syslog) syslog(priority, "STR", buf);
    else           fprintf(stderr, "STR", progname, buf);
    return(0);
}