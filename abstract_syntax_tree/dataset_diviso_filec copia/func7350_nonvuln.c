static void nfs4_proc_rename_setup(struct rpc_message *msg, struct inode *dir)
{
	struct nfs_server *server = NFS_SERVER(dir);
	struct nfs_renameargs *arg = msg->rpc_argp;
	struct nfs_renameres *res = msg->rpc_resp;

	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RENAME];
	arg->bitmask = server->attr_bitmask;
	res->server = server;
}