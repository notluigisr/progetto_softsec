static struct inode *v9fs_qid_iget(struct super_block *sb,
				   struct p9_qid *qid,
				   struct p9_wstat *st,
				   int new)
{
	dev_t rdev;
	int retval;
	umode_t umode;
	unsigned long i_ino;
	struct inode *inode;
	struct v9fs_session_info *v9ses = sb->s_fs_info;
	int (*test)(struct inode *, void *);

	if (new)
		test = v9fs_test_new_inode;
	else
		test = v9fs_test_inode;

	i_ino = v9fs_qid2ino(qid);
	inode = iget5_locked(sb, i_ino, test, v9fs_set_inode, st);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;
	
	inode->i_ino = i_ino;
	umode = p9mode2unixmode(v9ses, st, &rdev);
	retval = v9fs_init_inode(v9ses, inode, umode, rdev);
	if (retval)
		goto error;

	v9fs_stat2inode(st, inode, sb);
	v9fs_cache_inode_get_cookie(inode);
	unlock_new_inode(inode);
	return inode;
error:
	iget_failed(inode);
	return ERR_PTR(retval);

}