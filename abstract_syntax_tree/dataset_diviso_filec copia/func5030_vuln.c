static int path_set_acls(Item *item, const char *path) {
        int r = 0;
#if HAVE_ACL
        char fn[STRLEN("STR") + DECIMAL_STR_MAX(int)];
        _cleanup_close_ int fd = -1;
        struct stat st;

        assert(item);
        assert(path);

        fd = open(path, O_NOFOLLOW|O_CLOEXEC|O_PATH);
        if (fd < 0)
                return log_error_errno(errno, "STR", path);

        if (fstatat(fd, "", &st, AT_EMPTY_PATH) < 0)
                return log_error_errno(errno, "STR", path);

        if (S_ISLNK(st.st_mode)) {
                log_debug("STR", path);
                return 0;
        }

        xsprintf(fn, "STR", fd);

        if (item->acl_access)
                r = path_set_acl(fn, path, ACL_TYPE_ACCESS, item->acl_access, item->force);

        if (r == 0 && item->acl_default)
                r = path_set_acl(fn, path, ACL_TYPE_DEFAULT, item->acl_default, item->force);

        if (r > 0)
                return -r; 
        else if (r == -EOPNOTSUPP) {
                log_debug_errno(r, "STR", path);
                return 0;
        } else if (r < 0)
                log_error_errno(r, "STR", path);
#endif
        return r;
}