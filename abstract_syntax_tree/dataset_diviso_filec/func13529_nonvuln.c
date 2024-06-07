static struct nfs_client *__nfs_find_client(const struct sockaddr_in *addr, int nfsversion, int match_port)
{
	struct nfs_client *clp;

	list_for_each_entry(clp, &nfs_client_list, cl_share_link) {
		
		if (clp->cl_cons_state < 0)
			continue;

		
		if (clp->cl_nfsversion != nfsversion)
			continue;

		if (memcmp(&clp->cl_addr.sin_addr, &addr->sin_addr,
			   sizeof(clp->cl_addr.sin_addr)) != 0)
			continue;

		if (!match_port || clp->cl_addr.sin_port == addr->sin_port)
			goto found;
	}

	return NULL;

found:
	atomic_inc(&clp->cl_count);
	return clp;
}