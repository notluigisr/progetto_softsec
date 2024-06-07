struct nfs_server *nfs4_create_server(const struct nfs4_mount_data *data,
				      const char *hostname,
				      const struct sockaddr_in *addr,
				      const char *mntpath,
				      const char *ip_addr,
				      rpc_authflavor_t authflavour,
				      struct nfs_fh *mntfh)
{
	struct nfs_fattr fattr;
	struct nfs_server *server;
	int error;

	dprintk("STR");

	server = nfs_alloc_server();
	if (!server)
		return ERR_PTR(-ENOMEM);

	
	error = nfs4_set_client(server, hostname, addr, ip_addr, authflavour,
			data->proto, data->timeo, data->retrans);
	if (error < 0)
		goto error;

	
	error = nfs4_init_server(server, data, authflavour);
	if (error < 0)
		goto error;

	BUG_ON(!server->nfs_client);
	BUG_ON(!server->nfs_client->rpc_ops);
	BUG_ON(!server->nfs_client->rpc_ops->file_inode_ops);

	
	error = nfs4_path_walk(server, mntfh, mntpath);
	if (error < 0)
		goto error;

	dprintk("STR",
		(unsigned long long) server->fsid.major,
		(unsigned long long) server->fsid.minor);
	dprintk("STR", mntfh->size);

	error = nfs_probe_fsinfo(server, mntfh, &fattr);
	if (error < 0)
		goto error;

	BUG_ON(!server->nfs_client);
	BUG_ON(!server->nfs_client->rpc_ops);
	BUG_ON(!server->nfs_client->rpc_ops->file_inode_ops);

	spin_lock(&nfs_client_lock);
	list_add_tail(&server->client_link, &server->nfs_client->cl_superblocks);
	list_add_tail(&server->master_link, &nfs_volume_list);
	spin_unlock(&nfs_client_lock);

	server->mount_time = jiffies;
	dprintk("STR", server);
	return server;

error:
	nfs_free_server(server);
	dprintk("STR", error);
	return ERR_PTR(error);
}