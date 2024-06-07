static int btrfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	int err = 0;
	struct btrfs_root *root = BTRFS_I(dir)->root;
	struct btrfs_trans_handle *trans;

	if (inode->i_size > BTRFS_EMPTY_DIR_SIZE)
		return -ENOTEMPTY;
	if (btrfs_ino(inode) == BTRFS_FIRST_FREE_OBJECTID)
		return -EPERM;

	trans = __unlink_start_trans(dir, dentry);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	if (unlikely(btrfs_ino(inode) == BTRFS_EMPTY_SUBVOL_DIR_OBJECTID)) {
		err = btrfs_unlink_subvol(trans, root, dir,
					  BTRFS_I(inode)->location.objectid,
					  dentry->d_name.name,
					  dentry->d_name.len);
		goto out;
	}

	err = btrfs_orphan_add(trans, inode);
	if (err)
		goto out;

	
	err = btrfs_unlink_inode(trans, root, dir, dentry->d_inode,
				 dentry->d_name.name, dentry->d_name.len);
	if (!err)
		btrfs_i_size_write(inode, 0);
out:
	__unlink_end_trans(trans, root);
	btrfs_btree_balance_dirty(root);

	return err;
}