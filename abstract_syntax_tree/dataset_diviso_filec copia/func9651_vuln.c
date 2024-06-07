cifs_get_smb_ses(struct TCP_Server_Info *server, struct smb_vol *volume_info)
{
	int rc = -ENOMEM, xid;
	struct cifsSesInfo *ses;

	xid = GetXid();

	ses = cifs_find_smb_ses(server, volume_info->username);
	if (ses) {
		cFYI(1, "STR", ses->status);

		
		cifs_put_tcp_session(server);

		mutex_lock(&ses->session_mutex);
		rc = cifs_negotiate_protocol(xid, ses);
		if (rc) {
			mutex_unlock(&ses->session_mutex);
			
			cifs_put_smb_ses(ses);
			FreeXid(xid);
			return ERR_PTR(rc);
		}
		if (ses->need_reconnect) {
			cFYI(1, "STR");
			rc = cifs_setup_session(xid, ses,
						volume_info->local_nls);
			if (rc) {
				mutex_unlock(&ses->session_mutex);
				
				cifs_put_smb_ses(ses);
				FreeXid(xid);
				return ERR_PTR(rc);
			}
		}
		mutex_unlock(&ses->session_mutex);
		FreeXid(xid);
		return ses;
	}

	cFYI(1, "STR");
	ses = sesInfoAlloc();
	if (ses == NULL)
		goto get_ses_fail;

	
	ses->server = server;
	if (server->addr.sockAddr6.sin6_family == AF_INET6)
		sprintf(ses->serverName, "STR",
			&server->addr.sockAddr6.sin6_addr);
	else
		sprintf(ses->serverName, "STR",
			&server->addr.sockAddr.sin_addr.s_addr);

	if (volume_info->username)
		strncpy(ses->userName, volume_info->username,
			MAX_USERNAME_SIZE);

	
	if (volume_info->password) {
		ses->password = kstrdup(volume_info->password, GFP_KERNEL);
		if (!ses->password)
			goto get_ses_fail;
	}
	if (volume_info->domainname) {
		int len = strlen(volume_info->domainname);
		ses->domainName = kmalloc(len + 1, GFP_KERNEL);
		if (ses->domainName)
			strcpy(ses->domainName, volume_info->domainname);
	}
	ses->linux_uid = volume_info->linux_uid;
	ses->overrideSecFlg = volume_info->secFlg;

	mutex_lock(&ses->session_mutex);
	rc = cifs_negotiate_protocol(xid, ses);
	if (!rc)
		rc = cifs_setup_session(xid, ses, volume_info->local_nls);
	mutex_unlock(&ses->session_mutex);
	if (rc)
		goto get_ses_fail;

	
	write_lock(&cifs_tcp_ses_lock);
	list_add(&ses->smb_ses_list, &server->smb_ses_list);
	write_unlock(&cifs_tcp_ses_lock);

	FreeXid(xid);
	return ses;

get_ses_fail:
	sesInfoFree(ses);
	FreeXid(xid);
	return ERR_PTR(rc);
}