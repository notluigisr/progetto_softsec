bool smbXcli_tcon_is_dfs_share(struct smbXcli_tcon *tcon)
{
	if (tcon == NULL) {
		return false;
	}

	if (tcon->is_smb1) {
		if (tcon->smb1.optional_support & SMB_SHARE_IN_DFS) {
			return true;
		}

		return false;
	}

	if (tcon->smb2.capabilities & SMB2_SHARE_CAP_DFS) {
		return true;
	}

	return false;
}