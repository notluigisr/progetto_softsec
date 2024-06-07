evutil_make_internal_pipe_(evutil_socket_t fd[2])
{
	

#if defined(EVENT__HAVE_PIPE2)
	if (pipe2(fd, O_NONBLOCK|O_CLOEXEC) == 0)
		return 0;
#endif
#if defined(EVENT__HAVE_PIPE)
	if (pipe(fd) == 0) {
		if (evutil_fast_socket_nonblocking(fd[0]) < 0 ||
		    evutil_fast_socket_nonblocking(fd[1]) < 0 ||
		    evutil_fast_socket_closeonexec(fd[0]) < 0 ||
		    evutil_fast_socket_closeonexec(fd[1]) < 0) {
			close(fd[0]);
			close(fd[1]);
			fd[0] = fd[1] = -1;
			return -1;
		}
		return 0;
	} else {
		event_warn("STR", __func__);
	}
#endif

#ifdef _WIN32

#else

#endif
	if (evutil_socketpair(LOCAL_SOCKETPAIR_AF, SOCK_STREAM, 0, fd) == 0) {
		if (evutil_fast_socket_nonblocking(fd[0]) < 0 ||
		    evutil_fast_socket_nonblocking(fd[1]) < 0 ||
		    evutil_fast_socket_closeonexec(fd[0]) < 0 ||
		    evutil_fast_socket_closeonexec(fd[1]) < 0) {
			evutil_closesocket(fd[0]);
			evutil_closesocket(fd[1]);
			fd[0] = fd[1] = -1;
			return -1;
		}
		return 0;
	}
	fd[0] = fd[1] = -1;
	return -1;
}