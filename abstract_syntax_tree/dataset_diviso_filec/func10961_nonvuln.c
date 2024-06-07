static void lease_set_expire(GDHCPServer *dhcp_server,
			struct dhcp_lease *lease, uint32_t expire)
{
	dhcp_server->lease_list = g_list_remove(dhcp_server->lease_list, lease);

	lease->expire = expire;

	dhcp_server->lease_list = g_list_insert_sorted(dhcp_server->lease_list,
							lease, compare_expire);
}