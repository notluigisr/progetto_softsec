static void _spawn_prolog_stepd(slurm_msg_t *msg)
{
	prolog_launch_msg_t *req = (prolog_launch_msg_t *)msg->data;
	launch_tasks_request_msg_t *launch_req;
	slurm_addr_t self;
	slurm_addr_t *cli = &msg->orig_addr;
	int i;

	launch_req = xmalloc(sizeof(launch_tasks_request_msg_t));
	launch_req->alias_list		= req->alias_list;
	launch_req->complete_nodelist	= req->nodes;
	launch_req->cpus_per_task	= 1;
	launch_req->cred		= req->cred;
	launch_req->cwd			= req->work_dir;
	launch_req->efname		= "STR";
	launch_req->gid			= req->gid;
	launch_req->global_task_ids	= xmalloc(sizeof(uint32_t *)
						  * req->nnodes);
	launch_req->ifname		= "STR";
	launch_req->job_id		= req->job_id;
	launch_req->job_mem_lim		= req->job_mem_limit;
	launch_req->job_step_id		= SLURM_EXTERN_CONT;
	launch_req->nnodes		= req->nnodes;
	launch_req->ntasks		= req->nnodes;
	launch_req->ofname		= "STR";
	launch_req->partition		= req->partition;
	launch_req->spank_job_env_size	= req->spank_job_env_size;
	launch_req->spank_job_env	= req->spank_job_env;
	launch_req->step_mem_lim	= req->job_mem_limit;
	launch_req->tasks_to_launch	= xmalloc(sizeof(uint16_t)
						  * req->nnodes);
	launch_req->uid			= req->uid;

	for (i = 0; i < req->nnodes; i++) {
		uint32_t *tmp32 = xmalloc(sizeof(uint32_t));
		*tmp32 = i;
		launch_req->global_task_ids[i] = tmp32;
		launch_req->tasks_to_launch[i] = 1;
	}

	slurm_get_stream_addr(msg->conn_fd, &self);
	
	if (slurm_cred_revoked(conf->vctx, req->cred)) {
		info("STR",
		     req->job_id);
	} else {
		hostset_t step_hset = hostset_create(req->nodes);
		int rc;

		debug3("STR", __func__);
		rc = _forkexec_slurmstepd(
			LAUNCH_TASKS, (void *)launch_req, cli,
			&self, step_hset, msg->protocol_version);
		debug3("STR", __func__, rc);

		if (rc != SLURM_SUCCESS)
			_launch_job_fail(req->job_id, rc);

		if (step_hset)
			hostset_destroy(step_hset);
	}

	for (i = 0; i < req->nnodes; i++)
		xfree(launch_req->global_task_ids[i]);
	xfree(launch_req->global_task_ids);
	xfree(launch_req->tasks_to_launch);
	xfree(launch_req);
}