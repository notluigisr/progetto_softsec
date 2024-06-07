rsock_init_unixsock(VALUE sock, VALUE path, int server)
{
    struct sockaddr_un sockaddr;
    socklen_t sockaddrlen;
    int fd, status;
    rb_io_t *fptr;

    SafeStringValue(path);

    INIT_SOCKADDR_UN(&sockaddr, sizeof(struct sockaddr_un));
    if (sizeof(sockaddr.sun_path) < (size_t)RSTRING_LEN(path)) {
        rb_raise(rb_eArgError, "STR",
            RSTRING_LEN(path), (int)sizeof(sockaddr.sun_path));
    }
    memcpy(sockaddr.sun_path, RSTRING_PTR(path), RSTRING_LEN(path));
    sockaddrlen = rsock_unix_sockaddr_len(path);

    fd = rsock_socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
	rsock_sys_fail_path("STR", path);
    }

    if (server) {
        status = bind(fd, (struct sockaddr*)&sockaddr, sockaddrlen);
    }
    else {
	int prot;
	struct unixsock_arg arg;
	arg.sockaddr = &sockaddr;
	arg.sockaddrlen = sockaddrlen;
	arg.fd = fd;
        status = (int)rb_protect(unixsock_connect_internal, (VALUE)&arg, &prot);
	if (prot) {
	    close(fd);
	    rb_jump_tag(prot);
	}
    }

    if (status < 0) {
	close(fd);
        rsock_sys_fail_path("STR", path);
    }

    if (server) {
	if (listen(fd, SOMAXCONN) < 0) {
	    close(fd);
            rsock_sys_fail_path("STR", path);
	}
    }

    rsock_init_sock(sock, fd);
    if (server) {
	GetOpenFile(sock, fptr);
        fptr->pathv = rb_str_new_frozen(path);
    }

    return sock;
}