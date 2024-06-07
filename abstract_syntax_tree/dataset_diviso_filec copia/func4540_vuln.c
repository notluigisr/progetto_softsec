static void uv__process_child_init(const uv_process_options_t* options,
                                   int stdio_count,
                                   int (*pipes)[2],
                                   int error_fd) {
  int close_fd;
  int use_fd;
  int fd;

  if (options->flags & UV_PROCESS_DETACHED)
    setsid();

  for (fd = 0; fd < stdio_count; fd++) {
    close_fd = pipes[fd][0];
    use_fd = pipes[fd][1];

    if (use_fd < 0) {
      if (fd >= 3)
        continue;
      else {
        
        use_fd = open("STR", fd == 0 ? O_RDONLY : O_RDWR);
        close_fd = use_fd;

        if (use_fd == -1) {
        uv__write_int(error_fd, -errno);
          perror("STR");
          _exit(127);
        }
      }
    }

    if (fd == use_fd)
      uv__cloexec(use_fd, 0);
    else
      dup2(use_fd, fd);

    if (fd <= 2)
      uv__nonblock(fd, 0);

    if (close_fd != -1)
      uv__close(close_fd);
  }

  for (fd = 0; fd < stdio_count; fd++) {
    use_fd = pipes[fd][1];

    if (use_fd >= 0 && fd != use_fd)
      close(use_fd);
  }

  if (options->cwd != NULL && chdir(options->cwd)) {
    uv__write_int(error_fd, -errno);
    perror("STR");
    _exit(127);
  }

  if ((options->flags & UV_PROCESS_SETGID) && setgid(options->gid)) {
    uv__write_int(error_fd, -errno);
    perror("STR");
    _exit(127);
  }

  if ((options->flags & UV_PROCESS_SETUID) && setuid(options->uid)) {
    uv__write_int(error_fd, -errno);
    perror("STR");
    _exit(127);
  }

  if (options->env != NULL) {
    environ = options->env;
  }

  execvp(options->file, options->args);
  uv__write_int(error_fd, -errno);
  perror("STR");
  _exit(127);
}