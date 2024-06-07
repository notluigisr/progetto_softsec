struct btrfs_device *btrfs_find_device(struct btrfs_fs_devices *fs_devices,
				       u64 devid, u8 *uuid, u8 *fsid)
{
	struct btrfs_device *device;

	while (fs_devices) {
		if (!fsid ||
		    !memcmp(fs_devices->metadata_uuid, fsid, BTRFS_FSID_SIZE)) {
			device = find_device(fs_devices, devid, uuid);
			if (device)
				return device;
		}
		fs_devices = fs_devices->seed;
	}
	return NULL;
}