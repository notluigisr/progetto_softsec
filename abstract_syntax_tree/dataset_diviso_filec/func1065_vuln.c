rsock_s_recvfrom(VALUE sock, int argc, VALUE *argv, enum sock_recv_type from)
{
    rb_io_t *fptr;
    VALUE str;
    struct recvfrom_arg arg;
    VALUE len, flg;
    long buflen;
    long slen;

    rb_scan_args(argc, argv, "STR", &len, &flg, &str);

    if (flg == Qnil) arg.flags = 0;
    else             arg.flags = NUM2INT(flg);
    buflen = NUM2INT(len);
    str = rsock_strbuf(str, buflen);

    GetOpenFile(sock, fptr);
    if (rb_io_read_pending(fptr)) {
	rb_raise(rb_eIOError, "STR");
    }
    arg.fd = fptr->fd;
    arg.alen = (socklen_t)sizeof(arg.buf);
    arg.str = str;

    while (rb_io_check_closed(fptr),
	   rsock_maybe_wait_fd(arg.fd),
	   (slen = (long)rb_str_locktmp_ensure(str, recvfrom_locktmp,
	                                       (VALUE)&arg)) < 0) {
        if (!rb_io_wait_readable(fptr->fd)) {
            rb_sys_fail("STR");
        }
    }

    if (slen != RSTRING_LEN(str)) {
	rb_str_set_len(str, slen);
    }
    switch (from) {
      case RECV_RECV:
	return str;
      case RECV_IP:
#if 0
	if (arg.alen != sizeof(struct sockaddr_in)) {
	    rb_raise(rb_eTypeError, "STR");
	}
#endif
	if (arg.alen && arg.alen != sizeof(arg.buf)) 
	    return rb_assoc_new(str, rsock_ipaddr(&arg.buf.addr, arg.alen, fptr->mode & FMODE_NOREVLOOKUP));
	else
	    return rb_assoc_new(str, Qnil);

#ifdef HAVE_SYS_UN_H
      case RECV_UNIX:
        return rb_assoc_new(str, rsock_unixaddr(&arg.buf.un, arg.alen));
#endif
      case RECV_SOCKET:
	return rb_assoc_new(str, rsock_io_socket_addrinfo(sock, &arg.buf.addr, arg.alen));
      default:
	rb_bug("STR");
    }
}