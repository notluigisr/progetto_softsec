static int fuse_fsync(struct file *file, loff_t start, loff_t end,
		      int datasync)
{
	struct inode *inode = file->f_mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);
	int err;

	if (is_bad_inode(inode))
		return -EIO;

	inode_lock(inode);

	
	err = file_write_and_wait_range(file, start, end);
	if (err)
		goto out;

	fuse_sync_writes(inode);

	
	err = file_check_and_advance_wb_err(file);
	if (err)
		goto out;

	err = sync_inode_metadata(inode, 1);
	if (err)
		goto out;

	if (fc->no_fsync)
		goto out;

	err = fuse_fsync_common(file, start, end, datasync, FUSE_FSYNC);
	if (err == -ENOSYS) {
		fc->no_fsync = 1;
		err = 0;
	}
out:
	inode_unlock(inode);

	return err;
}