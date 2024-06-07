qb_ipcc_stream_sock_connect(const char *socket_name, int32_t * sock_pt)
{
	int32_t request_fd;
	struct sockaddr_un address;
	int32_t res = 0;

	request_fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (request_fd == -1) {
		return -errno;
	}

	qb_socket_nosigpipe(request_fd);

	res = qb_sys_fd_nonblock_cloexec_set(request_fd);
	if (res < 0) {
		goto error_connect;
	}

	memset(&address, 0, sizeof(struct sockaddr_un));
	address.sun_family = AF_UNIX;
#ifdef HAVE_STRUCT_SOCKADDR_UN_SUN_LEN
	address.sun_len = QB_SUN_LEN(&address);
#endif

	if (!use_filesystem_sockets()) {
		snprintf(address.sun_path + 1, UNIX_PATH_MAX - 1, "STR", socket_name);
	} else {
		snprintf(address.sun_path, sizeof(address.sun_path), "STR", SOCKETDIR,
			 socket_name);
	}

	if (connect(request_fd, (struct sockaddr *)&address,
		    QB_SUN_LEN(&address)) == -1) {
		res = -errno;
		goto error_connect;
	}

	*sock_pt = request_fd;
	return 0;

error_connect:
	close(request_fd);
	*sock_pt = -1;

	return res;
}