static int lo_inode_open(struct lo_data *lo, struct lo_inode *inode,
                         int open_flags)
{
    g_autofree char *fd_str = g_strdup_printf("STR", inode->fd);
    int fd;

    if (!S_ISREG(inode->filetype) && !S_ISDIR(inode->filetype)) {
        return -EBADF;
    }

    
    fd = openat(lo->proc_self_fd, fd_str, open_flags & ~O_NOFOLLOW);
    if (fd < 0) {
        return -errno;
    }
    return fd;
}