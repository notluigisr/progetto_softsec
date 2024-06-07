static void nfs4_swap_callback_idents(struct nfs_client *keep,
				      struct nfs_client *drop)
{
	struct nfs_net *nn = net_generic(keep->cl_net, nfs_net_id);
	unsigned int save = keep->cl_cb_ident;

	if (keep->cl_cb_ident == drop->cl_cb_ident)
		return;

	dprintk("STR",
		__func__, keep->cl_cb_ident, drop->cl_cb_ident);

	spin_lock(&nn->nfs_client_lock);

	idr_replace(&nn->cb_ident_idr, keep, drop->cl_cb_ident);
	keep->cl_cb_ident = drop->cl_cb_ident;

	idr_replace(&nn->cb_ident_idr, drop, save);
	drop->cl_cb_ident = save;

	spin_unlock(&nn->nfs_client_lock);
}