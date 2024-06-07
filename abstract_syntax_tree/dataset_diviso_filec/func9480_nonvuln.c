void smb1cli_session_set_action(struct smbXcli_session *session,
				uint16_t action)
{
	session->smb1.action = action;
}