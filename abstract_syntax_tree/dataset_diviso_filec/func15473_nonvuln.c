zfs_ace_fuid_mask_off(void)
{
	return (offsetof(zfs_ace_hdr_t, z_access_mask));
}