static void call_nt_transact_set_user_quota(connection_struct *conn,
					    struct smb_request *req,
					    uint16 **ppsetup,
					    uint32 setup_count,
					    char **ppparams,
					    uint32 parameter_count,
					    char **ppdata,
					    uint32 data_count,
					    uint32 max_data_count)
{
	char *params = *ppparams;
	char *pdata = *ppdata;
	int data_len=0,param_len=0;
	SMB_NTQUOTA_STRUCT qt;
	size_t sid_len;
	struct dom_sid sid;
	files_struct *fsp = NULL;

	ZERO_STRUCT(qt);

	
	if (get_current_uid(conn) != 0) {
		DEBUG(1,("STR"
			 "STR", lp_servicename(SNUM(conn)),
			 conn->session_info->unix_name));
		reply_nterror(req, NT_STATUS_ACCESS_DENIED);
		return;
	}

	

	if (parameter_count < 2) {
		DEBUG(0,("STR",parameter_count));
		reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
		return;
	}

	
	fsp = file_fsp(req, SVAL(params,0));
	if (!check_fsp_ntquota_handle(conn, req, fsp)) {
		DEBUG(3,("STR"));
		reply_nterror(req, NT_STATUS_INVALID_HANDLE);
		return;
	}

	if (data_count < 40) {
		DEBUG(0,("STR",data_count,40));
		reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
		return;
	}

	

	
	sid_len = IVAL(pdata,4);

	if (data_count < 40+sid_len || (40+sid_len < sid_len)) {
		DEBUG(0,("STR",data_count,(unsigned long)40+sid_len));
		reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
		return;
	}

	

	
	qt.usedspace = BVAL(pdata,16);

	
	qt.softlim = BVAL(pdata,24);

	
	qt.hardlim = BVAL(pdata,32);

	if (!sid_parse(pdata+40,sid_len,&sid)) {
		reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
		return;
	}

	DEBUGADD(8,("STR", sid_string_dbg(&sid)));

	

	if (vfs_set_ntquota(fsp, SMB_USER_QUOTA_TYPE, &sid, &qt)!=0) {
		reply_nterror(req, NT_STATUS_INTERNAL_ERROR);
		return;
	}

	send_nt_replies(conn, req, NT_STATUS_OK, params, param_len,
			pdata, data_len);
}