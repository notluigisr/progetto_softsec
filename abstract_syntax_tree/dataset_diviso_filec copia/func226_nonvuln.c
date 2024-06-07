static int btrfs_mknod(struct inode *dir, struct dentry *dentry,
			umode_t mode, dev_t rdev)
{
	struct btrfs_trans_handle *trans;
	struct btrfs_root *root = BTRFS_I(dir)->root;
	struct inode *inode = NULL;
	int err;
	int drop_inode = 0;
	u64 objectid;
	u64 index = 0;

	if (!new_valid_dev(rdev))
		return -EINVAL;

	
	trans = btrfs_start_transaction(root, 5);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	err = btrfs_find_free_ino(root, &objectid);
	if (err)
		goto out_unlock;

	inode = btrfs_new_inode(trans, root, dir, dentry->d_name.name,
				dentry->d_name.len, btrfs_ino(dir), objectid,
				mode, &index);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_unlock;
	}

	err = btrfs_init_inode_security(trans, inode, dir, &dentry->d_name);
	if (err) {
		drop_inode = 1;
		goto out_unlock;
	}

	err = btrfs_update_inode(trans, root, inode);
	if (err) {
		drop_inode = 1;
		goto out_unlock;
	}

	

	inode->i_op = &btrfs_special_inode_operations;
	err = btrfs_add_nondir(trans, dir, dentry, inode, 0, index);
	if (err)
		drop_inode = 1;
	else {
		init_special_inode(inode, inode->i_mode, rdev);
		btrfs_update_inode(trans, root, inode);
		d_instantiate(dentry, inode);
	}
out_unlock:
	btrfs_end_transaction(trans, root);
	btrfs_btree_balance_dirty(root);
	if (drop_inode) {
		inode_dec_link_count(inode);
		iput(inode);
	}
	return err;
}