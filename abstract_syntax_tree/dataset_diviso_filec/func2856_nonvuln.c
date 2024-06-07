static void nfs4_proc_write_rpc_prepare(struct rpc_task *task, struct nfs_write_data *data)
{
	if (nfs4_setup_sequence(NFS_SERVER(data->inode),
				&data->args.seq_args,
				&data->res.seq_res,
				task))
		return;
	rpc_call_start(task);
}