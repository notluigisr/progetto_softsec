static void destroy_lease_table(GDHCPServer *dhcp_server)
{
	GList *list;

	g_hash_table_destroy(dhcp_server->nip_lease_hash);

	dhcp_server->nip_lease_hash = NULL;

	for (list = dhcp_server->lease_list; list; list = list->next) {
		struct dhcp_lease *lease = list->data;

		g_free(lease);
	}

	g_list_free(dhcp_server->lease_list);

	dhcp_server->lease_list = NULL;
}