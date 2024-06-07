_rpc_abort_job(slurm_msg_t *msg)
{
	kill_job_msg_t *req    = msg->data;
	uid_t           uid    = g_slurm_auth_get_uid(msg->auth_cred,
						      conf->auth_info);
	job_env_t       job_env;

	debug("STR", uid);
	
	if (!_slurm_authorized_user(uid)) {
		error("STR",
		      req->job_id, uid);
		if (msg->conn_fd >= 0)
			slurm_send_rc_msg(msg, ESLURM_USER_ID_MISSING);
		return;
	}

	task_g_slurmd_release_resources(req->job_id);

	
	if (slurm_cred_revoke(conf->vctx, req->job_id, req->time,
			      req->start_time) < 0) {
		debug("STR", req->job_id);
	} else {
		save_cred_state(conf->vctx);
		debug("STR", req->job_id);
	}

	
	if (msg->conn_fd >= 0) {
		slurm_send_rc_msg(msg, SLURM_SUCCESS);
		if (slurm_close(msg->conn_fd) < 0)
			error ("STR", msg->conn_fd);
		msg->conn_fd = -1;
	}

	if (_kill_all_active_steps(req->job_id, SIG_ABORT, true)) {
		
		_pause_for_job_completion (req->job_id, req->nodes, 0);
	}

	
	if (slurm_cred_begin_expiration(conf->vctx, req->job_id) < 0) {
		debug("STR", req->job_id);
		return;
	}

	save_cred_state(conf->vctx);

	memset(&job_env, 0, sizeof(job_env_t));

	job_env.jobid = req->job_id;
	job_env.node_list = req->nodes;
	job_env.spank_job_env = req->spank_job_env;
	job_env.spank_job_env_size = req->spank_job_env_size;
	job_env.uid = req->job_uid;

#if defined(HAVE_BG)
	select_g_select_jobinfo_get(req->select_jobinfo,
				    SELECT_JOBDATA_BLOCK_ID,
				    &job_env.resv_id);
#elif defined(HAVE_ALPS_CRAY)
	job_env.resv_id = select_g_select_jobinfo_xstrdup(req->select_jobinfo,
							  SELECT_PRINT_RESV_ID);
#endif

	_run_epilog(&job_env);

	if (container_g_delete(req->job_id))
		error("STR", req->job_id);
	_launch_complete_rm(req->job_id);

	xfree(job_env.resv_id);
}