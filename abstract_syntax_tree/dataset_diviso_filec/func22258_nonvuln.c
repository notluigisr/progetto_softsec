rpc_clone_client(struct rpc_clnt *clnt)
{
	struct rpc_clnt *new;
	int err = -ENOMEM;

	new = kmemdup(clnt, sizeof(*new), GFP_KERNEL);
	if (!new)
		goto out_no_clnt;
	new->cl_parent = clnt;
	
	new->cl_autobind = 0;
	INIT_LIST_HEAD(&new->cl_tasks);
	spin_lock_init(&new->cl_lock);
	rpc_init_rtt(&new->cl_rtt_default, clnt->cl_timeout->to_initval);
	new->cl_metrics = rpc_alloc_iostats(clnt);
	if (new->cl_metrics == NULL)
		goto out_no_stats;
	if (clnt->cl_principal) {
		new->cl_principal = kstrdup(clnt->cl_principal, GFP_KERNEL);
		if (new->cl_principal == NULL)
			goto out_no_principal;
	}
	atomic_set(&new->cl_count, 1);
	err = rpc_setup_pipedir(new, clnt->cl_program->pipe_dir_name);
	if (err != 0)
		goto out_no_path;
	if (new->cl_auth)
		atomic_inc(&new->cl_auth->au_count);
	xprt_get(clnt->cl_xprt);
	atomic_inc(&clnt->cl_count);
	rpc_register_client(new);
	rpciod_up();
	return new;
out_no_path:
	kfree(new->cl_principal);
out_no_principal:
	rpc_free_iostats(new->cl_metrics);
out_no_stats:
	kfree(new);
out_no_clnt:
	dprintk("STR", __func__, err);
	return ERR_PTR(err);
}