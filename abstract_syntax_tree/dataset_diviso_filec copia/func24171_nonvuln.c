int vfs_lstat_smb_fname(struct connection_struct *conn, const char *fname,
			SMB_STRUCT_STAT *psbuf)
{
	struct smb_filename *smb_fname = NULL;
	NTSTATUS status;
	int ret;

	status = create_synthetic_smb_fname_split(talloc_tos(), fname, NULL,
						  &smb_fname);
	if (!NT_STATUS_IS_OK(status)) {
		errno = map_errno_from_nt_status(status);
		return -1;
	}

	ret = SMB_VFS_LSTAT(conn, smb_fname);
	if (ret != -1) {
		*psbuf = smb_fname->st;
	}

	TALLOC_FREE(smb_fname);
	return ret;
}