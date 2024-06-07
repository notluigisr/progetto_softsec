static void lo_open(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
    struct lo_data *lo = lo_data(req);
    struct lo_inode *inode = lo_inode(req, ino);
    int err;

    fuse_log(FUSE_LOG_DEBUG, "STR"
             "STR", ino, fi->flags, fi->kill_priv);

    if (!inode) {
        fuse_reply_err(req, EBADF);
        return;
    }

    err = lo_do_open(lo, inode, -1, fi);
    lo_inode_put(lo, &inode);
    if (err) {
        fuse_reply_err(req, err);
    } else {
        fuse_reply_open(req, fi);
    }
}