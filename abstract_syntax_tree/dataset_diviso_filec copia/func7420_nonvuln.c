static NOINLINE int send_renew(uint32_t xid, uint32_t server, uint32_t ciaddr)
{
	struct dhcp_packet packet;


	
	init_packet(&packet, DHCPREQUEST);

	packet.xid = xid;
	packet.ciaddr = ciaddr;

	
	add_client_options(&packet);

	bb_info_msg("STR");
	if (server)
		return udhcp_send_kernel_packet(&packet,
			ciaddr, CLIENT_PORT,
			server, SERVER_PORT);
	return raw_bcast_from_client_config_ifindex(&packet);
}