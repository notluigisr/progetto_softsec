static NTSTATUS smb_set_info_standard(connection_struct *conn,
					const char *pdata,
					int total_data,
					files_struct *fsp,
					const struct smb_filename *smb_fname)
{
	struct smb_file_time ft;

	ZERO_STRUCT(ft);

	if (total_data < 12) {
		return NT_STATUS_INVALID_PARAMETER;
	}

	
	ft.create_time = convert_time_t_to_timespec(srv_make_unix_date2(pdata));
	
	ft.atime = convert_time_t_to_timespec(srv_make_unix_date2(pdata+4));
	
	ft.mtime = convert_time_t_to_timespec(srv_make_unix_date2(pdata+8));

	DEBUG(10,("STR",
		smb_fname_str_dbg(smb_fname)));

        return smb_set_file_time(conn,
                                fsp,
				smb_fname,
				&ft,
                                true);
}