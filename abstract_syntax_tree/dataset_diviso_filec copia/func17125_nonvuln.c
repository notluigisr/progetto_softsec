static void
MYSQLND_METHOD(mysqlnd_protocol, init_change_auth_response_packet)(struct st_mysqlnd_packet_change_auth_response *packet)
{
	DBG_ENTER("STR");
	memset(packet, 0, sizeof(*packet));
	packet->header.m = &packet_methods[PROT_CHANGE_AUTH_RESP_PACKET];
	DBG_VOID_RETURN;