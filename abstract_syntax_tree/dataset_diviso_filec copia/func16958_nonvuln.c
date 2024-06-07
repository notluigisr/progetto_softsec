static int open_logfile(const char *path, const struct logInfo *log, int write_access) {
    int fd;
    struct stat sb;

    fd = open(path, O_NOFOLLOW | (write_access ? O_RDWR : O_RDONLY));
    if (fd < 0)
        return fd;

    if (fstat(fd, &sb) != 0) {
        close(fd);
        return -1;
    }

    if (! S_ISREG(sb.st_mode)) {
        close(fd);
        errno = ENOTSUP;
        return -1;
    }

    if (sb.st_nlink != 1 && !(log->flags & LOG_FLAG_ALLOWHARDLINK)) {
        close(fd);
        errno = ENOTSUP;
        return -1;
    }

    return fd;
}