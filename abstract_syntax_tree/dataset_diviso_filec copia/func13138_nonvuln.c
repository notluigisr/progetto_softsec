static int fix_permissions(
                int fd,
                const char *filename,
                const char *target,
                const char *context[_CONTEXT_MAX],
                uid_t uid) {

        int r;

        assert(fd >= 0);
        assert(target);
        assert(context);

        
        (void) fchmod(fd, 0640);
        (void) fix_acl(fd, uid);
        (void) fix_xattr(fd, context);

        if (fsync(fd) < 0)
                return log_error_errno(errno, "STR", coredump_tmpfile_name(filename));

        (void) fsync_directory_of_file(fd);

        r = link_tmpfile(fd, filename, target);
        if (r < 0)
                return log_error_errno(r, "STR", target);

        return 0;
}