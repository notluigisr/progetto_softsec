static bool ad_convert_truncate(vfs_handle_struct *handle,
				struct adouble *ad,
				const struct smb_filename *smb_fname)
{
	int rc;
	off_t newlen;

	newlen = ADEDOFF_RFORK_DOT_UND + ad_getentrylen(ad, ADEID_RFORK);

	rc = SMB_VFS_FTRUNCATE(ad->ad_fsp, newlen);
	if (rc != 0) {
		return false;
	}

	return true;
}