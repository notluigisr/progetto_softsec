struct nfs_server *nfs_create_server(const struct nfs_mount_data *data,
				     struct nfs_fh *mntfh)
{
	struct nfs_server *server;
	struct nfs_fattr fattr;
	int error;

	server = nfs_alloc_server();
	if (!server)
		return ERR_PTR(-ENOMEM);

	
	error = nfs_init_server(server, data);
	if (error < 0)
		goto error;

	BUG_ON(!server->nfs_client);
	BUG_ON(!server->nfs_client->rpc_ops);
	BUG_ON(!server->nfs_client->rpc_ops->file_inode_ops);

	
	error = nfs_probe_fsinfo(server, mntfh, &fattr);
	if (error < 0)
		goto error;
	if (!(fattr.valid & NFS_ATTR_FATTR)) {
		error = server->nfs_client->rpc_ops->getattr(server, mntfh, &fattr);
		if (error < 0) {
			dprintk("STR", -error);
			goto error;
		}
	}
	memcpy(&server->fsid, &fattr.fsid, sizeof(server->fsid));

	dprintk("STR",
		(unsigned long long) server->fsid.major,
		(unsigned long long) server->fsid.minor);

	BUG_ON(!server->nfs_client);
	BUG_ON(!server->nfs_client->rpc_ops);
	BUG_ON(!server->nfs_client->rpc_ops->file_inode_ops);

	spin_lock(&nfs_client_lock);
	list_add_tail(&server->client_link, &server->nfs_client->cl_superblocks);
	list_add_tail(&server->master_link, &nfs_volume_list);
	spin_unlock(&nfs_client_lock);

	server->mount_time = jiffies;
	return server;

error:
	nfs_free_server(server);
	return ERR_PTR(error);
}