int ssh_scp_response(ssh_scp scp, char **response){
	unsigned char code;
	int r;
	char msg[128];
	if(scp==NULL)
	    return SSH_ERROR;
	r=ssh_channel_read(scp->channel,&code,1,0);
	if(r == SSH_ERROR)
		return SSH_ERROR;
	if(code == 0)
		return 0;
	if(code > 2){
		ssh_set_error(scp->session,SSH_FATAL, "STR", code);
		scp->state=SSH_SCP_ERROR;
		return SSH_ERROR;
	}
	r=ssh_scp_read_string(scp,msg,sizeof(msg));
	if(r==SSH_ERROR)
		return r;
	
	if(code == 1){
		ssh_set_error(scp->session,SSH_REQUEST_DENIED, "STR", msg);
		SSH_LOG(SSH_LOG_RARE,"STR", msg);
		if(response)
			*response=strdup(msg);
		return 1;
	}
	if(code == 2){
		ssh_set_error(scp->session,SSH_FATAL, "STR", msg);
		if(response)
			*response=strdup(msg);
		return 2;
	}
	
	return SSH_ERROR;
}