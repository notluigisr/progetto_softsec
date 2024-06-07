static int _nfs4_proc_destroy_clientid(struct nfs_client *clp,
		const struct cred *cred)
{
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_DESTROY_CLIENTID],
		.rpc_argp = clp,
		.rpc_cred = cred,
	};
	int status;

	status = rpc_call_sync(clp->cl_rpcclient, &msg,
			       RPC_TASK_TIMEOUT | RPC_TASK_NO_ROUND_ROBIN);
	trace_nfs4_destroy_clientid(clp, status);
	if (status)
		dprintk("STR"
			"STR", status, clp->cl_hostname);
	return status;
}