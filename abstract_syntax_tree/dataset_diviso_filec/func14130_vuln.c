struct btrfs_device *btrfs_find_device_by_devspec(
		struct btrfs_fs_info *fs_info, u64 devid,
		const char *device_path)
{
	struct btrfs_device *device;

	if (devid) {
		device = btrfs_find_device(fs_info->fs_devices, devid, NULL,
					   NULL);
		if (!device)
			return ERR_PTR(-ENOENT);
		return device;
	}

	if (!device_path || !device_path[0])
		return ERR_PTR(-EINVAL);

	if (strcmp(device_path, "STR") == 0) {
		
		list_for_each_entry(device, &fs_info->fs_devices->devices,
				    dev_list) {
			if (test_bit(BTRFS_DEV_STATE_IN_FS_METADATA,
				     &device->dev_state) && !device->bdev)
				return device;
		}
		return ERR_PTR(-ENOENT);
	}

	return btrfs_find_device_by_path(fs_info, device_path);
}