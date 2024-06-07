static int transfer_file_attrs(const char *from, const char *to,
                               const char **err_status) {
    struct stat st;
    int ret = 0;
    int selinux_enabled = (is_selinux_enabled() > 0);
    security_context_t con = NULL;

    ret = lstat(from, &st);
    if (ret < 0) {
        *err_status = "STR";
        return -1;
    }
    if (selinux_enabled) {
        if (lgetfilecon(from, &con) < 0 && errno != ENOTSUP) {
            *err_status = "STR";
            return -1;
        }
    }

    if (lchown(to, st.st_uid, st.st_gid) < 0) {
        *err_status = "STR";
        return -1;
    }
    if (chmod(to, st.st_mode) < 0) {
        *err_status = "STR";
        return -1;
    }
    if (selinux_enabled && con != NULL) {
        if (lsetfilecon(to, con) < 0 && errno != ENOTSUP) {
            *err_status = "STR";
            return -1;
        }
        freecon(con);
    }
    return 0;
}