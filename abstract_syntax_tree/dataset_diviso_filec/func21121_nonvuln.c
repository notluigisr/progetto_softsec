static void nfs4_destroy_server(struct nfs_server *server)
{
	LIST_HEAD(freeme);

	nfs_server_return_all_delegations(server);
	unset_pnfs_layoutdriver(server);
	nfs4_purge_state_owners(server, &freeme);
	nfs4_free_state_owners(&freeme);
}