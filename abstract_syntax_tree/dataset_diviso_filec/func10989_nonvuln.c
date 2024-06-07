smb2_set_credits(struct TCP_Server_Info *server, const int val)
{
	int scredits, in_flight;

	spin_lock(&server->req_lock);
	server->credits = val;
	if (val == 1)
		server->reconnect_instance++;
	scredits = server->credits;
	in_flight = server->in_flight;
	spin_unlock(&server->req_lock);

	trace_smb3_set_credits(server->CurrentMid,
			server->conn_id, server->hostname, scredits, val, in_flight);
	cifs_dbg(FYI, "STR", __func__, val);

	
	if (val == 1)
		cifs_dbg(FYI, "STR");
}