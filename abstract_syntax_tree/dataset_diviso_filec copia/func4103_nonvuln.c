bool proc_fill_cache(struct file *file, struct dir_context *ctx,
	const char *name, int len,
	instantiate_t instantiate, struct task_struct *task, const void *ptr)
{
	struct dentry *child, *dir = file->f_path.dentry;
	struct qstr qname = QSTR_INIT(name, len);
	struct inode *inode;
	unsigned type;
	ino_t ino;

	child = d_hash_and_lookup(dir, &qname);
	if (!child) {
		DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
		child = d_alloc_parallel(dir, &qname, &wq);
		if (IS_ERR(child))
			goto end_instantiate;
		if (d_in_lookup(child)) {
			int err = instantiate(d_inode(dir), child, task, ptr);
			d_lookup_done(child);
			if (err < 0) {
				dput(child);
				goto end_instantiate;
			}
		}
	}
	inode = d_inode(child);
	ino = inode->i_ino;
	type = inode->i_mode >> 12;
	dput(child);
	return dir_emit(ctx, name, len, ino, type);

end_instantiate:
	return dir_emit(ctx, name, len, 1, DT_UNKNOWN);
}