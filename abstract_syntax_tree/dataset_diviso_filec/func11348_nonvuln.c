int btrfs_resume_balance_async(struct btrfs_fs_info *fs_info)
{
	struct task_struct *tsk;

	mutex_lock(&fs_info->balance_mutex);
	if (!fs_info->balance_ctl) {
		mutex_unlock(&fs_info->balance_mutex);
		return 0;
	}
	mutex_unlock(&fs_info->balance_mutex);

	if (btrfs_test_opt(fs_info, SKIP_BALANCE)) {
		btrfs_info(fs_info, "STR");
		return 0;
	}

	
	spin_lock(&fs_info->balance_lock);
	fs_info->balance_ctl->flags |= BTRFS_BALANCE_RESUME;
	spin_unlock(&fs_info->balance_lock);

	tsk = kthread_run(balance_kthread, fs_info, "STR");
	return PTR_ERR_OR_ZERO(tsk);
}