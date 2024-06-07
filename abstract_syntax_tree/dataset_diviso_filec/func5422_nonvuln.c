static int record_root_in_trans(struct btrfs_trans_handle *trans,
			       struct btrfs_root *root,
			       int force)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	int ret = 0;

	if ((test_bit(BTRFS_ROOT_SHAREABLE, &root->state) &&
	    root->last_trans < trans->transid) || force) {
		WARN_ON(root == fs_info->extent_root);
		WARN_ON(!force && root->commit_root != root->node);

		
		set_bit(BTRFS_ROOT_IN_TRANS_SETUP, &root->state);

		
		smp_wmb();

		spin_lock(&fs_info->fs_roots_radix_lock);
		if (root->last_trans == trans->transid && !force) {
			spin_unlock(&fs_info->fs_roots_radix_lock);
			return 0;
		}
		radix_tree_tag_set(&fs_info->fs_roots_radix,
				   (unsigned long)root->root_key.objectid,
				   BTRFS_ROOT_TRANS_TAG);
		spin_unlock(&fs_info->fs_roots_radix_lock);
		root->last_trans = trans->transid;

		
		ret = btrfs_init_reloc_root(trans, root);
		smp_mb__before_atomic();
		clear_bit(BTRFS_ROOT_IN_TRANS_SETUP, &root->state);
	}
	return ret;
}