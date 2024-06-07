struct nfs_client *nfs4_init_client(struct nfs_client *clp,
				    const struct nfs_client_initdata *cl_init)
{
	char buf[INET6_ADDRSTRLEN + 1];
	const char *ip_addr = cl_init->ip_addr;
	struct nfs_client *old;
	int error;

	if (clp->cl_cons_state == NFS_CS_READY)
		
		return clp;

	
	clp->rpc_ops = &nfs_v4_clientops;

	if (clp->cl_minorversion != 0)
		__set_bit(NFS_CS_INFINITE_SLOTS, &clp->cl_flags);
	__set_bit(NFS_CS_DISCRTRY, &clp->cl_flags);
	__set_bit(NFS_CS_NO_RETRANS_TIMEOUT, &clp->cl_flags);

	error = nfs_create_rpc_client(clp, cl_init, RPC_AUTH_GSS_KRB5I);
	if (error == -EINVAL)
		error = nfs_create_rpc_client(clp, cl_init, RPC_AUTH_UNIX);
	if (error < 0)
		goto error;

	
	if (ip_addr == NULL) {
		struct sockaddr_storage cb_addr;
		struct sockaddr *sap = (struct sockaddr *)&cb_addr;

		error = rpc_localaddr(clp->cl_rpcclient, sap, sizeof(cb_addr));
		if (error < 0)
			goto error;
		error = rpc_ntop(sap, buf, sizeof(buf));
		if (error < 0)
			goto error;
		ip_addr = (const char *)buf;
	}
	strlcpy(clp->cl_ipaddr, ip_addr, sizeof(clp->cl_ipaddr));

	error = nfs_idmap_new(clp);
	if (error < 0) {
		dprintk("STR",
			__func__, error);
		goto error;
	}
	__set_bit(NFS_CS_IDMAP, &clp->cl_res_state);

	error = nfs4_init_client_minor_version(clp);
	if (error < 0)
		goto error;

	error = nfs4_discover_server_trunking(clp, &old);
	if (error < 0)
		goto error;

	if (clp != old) {
		clp->cl_preserve_clid = true;
		
		nfs_mark_client_ready(clp, -EPERM);
	}
	clear_bit(NFS_CS_TSM_POSSIBLE, &clp->cl_flags);
	nfs_put_client(clp);
	return old;

error:
	nfs_mark_client_ready(clp, error);
	nfs_put_client(clp);
	return ERR_PTR(error);
}