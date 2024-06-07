SMB2_select_sec(struct cifs_ses *ses, struct SMB2_sess_data *sess_data)
{
	int type;

	type = smb2_select_sectype(ses->server, ses->sectype);
	cifs_dbg(FYI, "STR", type);
	if (type == Unspecified) {
		cifs_dbg(VFS,
			"STR");
		return -EINVAL;
	}

	switch (type) {
	case Kerberos:
		sess_data->func = SMB2_auth_kerberos;
		break;
	case RawNTLMSSP:
		sess_data->func = SMB2_sess_auth_rawntlmssp_negotiate;
		break;
	default:
		cifs_dbg(VFS, "STR", type);
		return -EOPNOTSUPP;
	}

	return 0;
}