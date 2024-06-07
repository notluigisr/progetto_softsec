void update_ioctl_balance_args(struct btrfs_fs_info *fs_info, int lock,
			       struct btrfs_ioctl_balance_args *bargs)
{
	struct btrfs_balance_control *bctl = fs_info->balance_ctl;

	bargs->flags = bctl->flags;

	if (atomic_read(&fs_info->balance_running))
		bargs->state |= BTRFS_BALANCE_STATE_RUNNING;
	if (atomic_read(&fs_info->balance_pause_req))
		bargs->state |= BTRFS_BALANCE_STATE_PAUSE_REQ;
	if (atomic_read(&fs_info->balance_cancel_req))
		bargs->state |= BTRFS_BALANCE_STATE_CANCEL_REQ;

	memcpy(&bargs->data, &bctl->data, sizeof(bargs->data));
	memcpy(&bargs->meta, &bctl->meta, sizeof(bargs->meta));
	memcpy(&bargs->sys, &bctl->sys, sizeof(bargs->sys));

	if (lock) {
		spin_lock(&fs_info->balance_lock);
		memcpy(&bargs->stat, &bctl->stat, sizeof(bargs->stat));
		spin_unlock(&fs_info->balance_lock);
	} else {
		memcpy(&bargs->stat, &bctl->stat, sizeof(bargs->stat));
	}
}