void btrfs_rm_dev_replace_remove_srcdev(struct btrfs_device *srcdev)
{
	struct btrfs_fs_devices *fs_devices;

	lockdep_assert_held(&srcdev->fs_info->fs_devices->device_list_mutex);

	
	fs_devices = srcdev->fs_devices;

	list_del_rcu(&srcdev->dev_list);
	list_del(&srcdev->dev_alloc_list);
	fs_devices->num_devices--;
	if (test_bit(BTRFS_DEV_STATE_MISSING, &srcdev->dev_state))
		fs_devices->missing_devices--;

	if (test_bit(BTRFS_DEV_STATE_WRITEABLE, &srcdev->dev_state))
		fs_devices->rw_devices--;

	if (srcdev->bdev)
		fs_devices->open_devices--;
}