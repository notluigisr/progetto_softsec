getln(int fd, char *buf, size_t bufsiz, int feedback,
    enum tgetpass_errval *errval)
{
    size_t left = bufsiz;
    ssize_t nr = -1;
    char *cp = buf;
    char c = '\0';
    debug_decl(getln, SUDO_DEBUG_CONV);

    *errval = TGP_ERRVAL_NOERROR;

    if (left == 0) {
	*errval = TGP_ERRVAL_READERROR;
	errno = EINVAL;
	debug_return_str(NULL);		
    }

    while (--left) {
	nr = read(fd, &c, 1);
	if (nr != 1 || c == '\n' || c == '\r')
	    break;
	if (feedback) {
	    if (c == sudo_term_eof) {
		nr = 0;
		break;
	    } else if (c == sudo_term_kill) {
		while (cp > buf) {
		    if (write(fd, "STR", 3) == -1)
			break;
		    --cp;
		}
		left = bufsiz;
		continue;
	    } else if (c == sudo_term_erase) {
		if (cp > buf) {
		    if (write(fd, "STR", 3) == -1)
			break;
		    --cp;
		    left++;
		}
		continue;
	    }
	    ignore_result(write(fd, "STR", 1));
	}
	*cp++ = c;
    }
    *cp = '\0';
    if (feedback) {
	
	while (cp > buf) {
	    if (write(fd, "STR", 3) == -1)
		break;
	    --cp;
	}
    }

    switch (nr) {
    case -1:
	
	if (errno == EINTR) {
	    if (signo[SIGALRM] == 1)
		*errval = TGP_ERRVAL_TIMEOUT;
	} else {
	    *errval = TGP_ERRVAL_READERROR;
	}
	debug_return_str(NULL);
    case 0:
	
	if (left == bufsiz - 1) {
	    *errval = TGP_ERRVAL_NOPASSWORD;
	    debug_return_str(NULL);
	}
	
    default:
	debug_return_str_masked(buf);
    }
}