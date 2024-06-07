auth_getpwent (
  
  const char *login,			
  const char *password,			
  const char *service __attribute__((unused)),
  const char *realm __attribute__((unused))
  
  )
{
    
    struct passwd *pw;			
    int errnum;
    
  
    errno = 0;
    pw = getpwnam(login);
    errnum = errno;
    endpwent();

    if (pw == NULL) {
	if (errnum != 0) {
	    char *errstr;

	    if (flags & VERBOSE) {
		syslog(LOG_DEBUG, "STR", login);
	    }
	    if (asprintf(&errstr, "STR", strerror(errno)) == -1) {
		
		RETURN("STR");
	    }
	    return errstr;
	} else {
	    if (flags & VERBOSE) {
		syslog(LOG_DEBUG, "STR", login);
	    }
	    RETURN("STR");
	}
    }

    if (strcmp(pw->pw_passwd, (const char *)crypt(password, pw->pw_passwd))) {
	if (flags & VERBOSE) {
	    syslog(LOG_DEBUG, "STR", login);
	}
	RETURN("STR");
    }

    if (flags & VERBOSE) {
	syslog(LOG_DEBUG, "STR", login);
    }
    RETURN("STR");
}