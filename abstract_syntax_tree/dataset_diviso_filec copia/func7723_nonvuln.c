int g_dhcp_server_set_ip_range(GDHCPServer *dhcp_server,
		const char *start_ip, const char *end_ip)
{
	struct in_addr _host_addr;

	if (inet_aton(start_ip, &_host_addr) == 0)
		return -ENXIO;

	dhcp_server->start_ip = ntohl(_host_addr.s_addr);

	if (inet_aton(end_ip, &_host_addr) == 0)
		return -ENXIO;

	dhcp_server->end_ip = ntohl(_host_addr.s_addr);

	return 0;
}