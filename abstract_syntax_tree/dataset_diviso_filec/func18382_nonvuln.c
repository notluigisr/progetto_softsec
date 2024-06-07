static struct st_mysqlnd_packet_auth *
MYSQLND_METHOD(mysqlnd_protocol, get_auth_packet)(MYSQLND_PROTOCOL * const protocol, zend_bool persistent TSRMLS_DC)
{
	struct st_mysqlnd_packet_auth * packet = mnd_pecalloc(1, packet_methods[PROT_AUTH_PACKET].struct_size, persistent);
	DBG_ENTER("STR");
	if (packet) {
		packet->header.m = &packet_methods[PROT_AUTH_PACKET];
		packet->header.persistent = persistent;
	}
	DBG_RETURN(packet);