static void call_trans2findnotifynext(connection_struct *conn,
				      struct smb_request *req,
				      char **pparams, int total_params,
				      char **ppdata, int total_data,
				      unsigned int max_data_bytes)
{
	char *params = *pparams;

	DEBUG(3,("STR"));

	
	*pparams = (char *)SMB_REALLOC(*pparams,4);
	if (*pparams == NULL) {
		reply_nterror(req, NT_STATUS_NO_MEMORY);
		return;
	}
	params = *pparams;

	SSVAL(params,0,0); 
	SSVAL(params,2,0); 

	send_trans2_replies(conn, req, NT_STATUS_OK, params, 4, *ppdata, 0, max_data_bytes);

	return;
}