int btrfs_cancel_balance(struct btrfs_fs_info *fs_info)
{
	mutex_lock(&fs_info->balance_mutex);
	if (!fs_info->balance_ctl) {
		mutex_unlock(&fs_info->balance_mutex);
		return -ENOTCONN;
	}

	
	if (sb_rdonly(fs_info->sb)) {
		mutex_unlock(&fs_info->balance_mutex);
		return -EROFS;
	}

	atomic_inc(&fs_info->balance_cancel_req);
	
	if (test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags)) {
		mutex_unlock(&fs_info->balance_mutex);
		wait_event(fs_info->balance_wait_q,
			   !test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags));
		mutex_lock(&fs_info->balance_mutex);
	} else {
		mutex_unlock(&fs_info->balance_mutex);
		
		mutex_lock(&fs_info->balance_mutex);

		if (fs_info->balance_ctl) {
			reset_balance_state(fs_info);
			clear_bit(BTRFS_FS_EXCL_OP, &fs_info->flags);
			btrfs_info(fs_info, "STR");
		}
	}

	BUG_ON(fs_info->balance_ctl ||
		test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags));
	atomic_dec(&fs_info->balance_cancel_req);
	mutex_unlock(&fs_info->balance_mutex);
	return 0;
}