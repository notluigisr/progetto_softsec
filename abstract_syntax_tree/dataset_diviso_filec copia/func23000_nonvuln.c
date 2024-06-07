static int setup_raw_socket(RemoteServer *s, const char *address) {
        int fd;

        fd = make_socket_fd(LOG_INFO, address, SOCK_STREAM, SOCK_CLOEXEC);
        if (fd < 0)
                return fd;

        return journal_remote_add_raw_socket(s, fd);
}