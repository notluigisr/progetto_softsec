int rm_rf_child(int fd, const char *name, RemoveFlags flags) {

        

        if (fd < 0)
                return -EBADF;

        if (!filename_is_valid(name))
                return -EINVAL;

        if ((flags & (REMOVE_ROOT|REMOVE_MISSING_OK)) != 0) 
                return -EINVAL;

        if (FLAGS_SET(flags, REMOVE_ONLY_DIRECTORIES|REMOVE_SUBVOLUME))
                return -EINVAL;

        return rm_rf_children_inner(fd, name, -1, flags, NULL);
}