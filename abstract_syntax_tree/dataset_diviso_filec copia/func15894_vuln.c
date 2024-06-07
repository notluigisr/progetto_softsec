static void _rpc_prolog(slurm_msg_t *msg)
{
	int rc = SLURM_SUCCESS;
	prolog_launch_msg_t *req = (prolog_launch_msg_t *)msg->data;
	job_env_t job_env;
	bool     first_job_run;
	uid_t    req_uid;

	if (req == NULL)
		return;

	req_uid = g_slurm_auth_get_uid(msg->auth_cred, conf->auth_info);
	if (!_slurm_authorized_user(req_uid)) {
		error("STR",
		      (unsigned int) req_uid);
		return;
	}

	if (slurm_send_rc_msg(msg, rc) < 0) {
		error("STR");
	}
	if (rc) {
		int term_sig, exit_status;
		if (WIFSIGNALED(rc)) {
			exit_status = 0;
			term_sig    = WTERMSIG(rc);
		} else {
			exit_status = WEXITSTATUS(rc);
			term_sig    = 0;
		}
		error("STR",
		      req->job_id, exit_status, term_sig);
		rc = ESLURMD_PROLOG_FAILED;
	}

	slurm_mutex_lock(&prolog_mutex);
	first_job_run = !slurm_cred_jobid_cached(conf->vctx, req->job_id);
	if (first_job_run) {
		if (slurmctld_conf.prolog_flags & PROLOG_FLAG_CONTAIN)
			_make_prolog_mem_container(msg);

		if (container_g_create(req->job_id))
			error("STR", req->job_id);

		slurm_cred_insert_jobid(conf->vctx, req->job_id);
		_add_job_running_prolog(req->job_id);
		slurm_mutex_unlock(&prolog_mutex);

		memset(&job_env, 0, sizeof(job_env_t));

		job_env.jobid = req->job_id;
		job_env.step_id = 0;	
		job_env.node_list = req->nodes;
		job_env.partition = req->partition;
		job_env.spank_job_env = req->spank_job_env;
		job_env.spank_job_env_size = req->spank_job_env_size;
		job_env.uid = req->uid;
		job_env.user_name = req->user_name;
#if defined(HAVE_BG)
		select_g_select_jobinfo_get(req->select_jobinfo,
					    SELECT_JOBDATA_BLOCK_ID,
					    &job_env.resv_id);
#elif defined(HAVE_ALPS_CRAY)
		job_env.resv_id = select_g_select_jobinfo_xstrdup(
			req->select_jobinfo, SELECT_PRINT_RESV_ID);
#endif
		rc = _run_prolog(&job_env, req->cred);

		if (rc) {
			int term_sig, exit_status;
			if (WIFSIGNALED(rc)) {
				exit_status = 0;
				term_sig    = WTERMSIG(rc);
			} else {
				exit_status = WEXITSTATUS(rc);
				term_sig    = 0;
			}
			error("STR",
			      req->job_id, exit_status, term_sig);
			rc = ESLURMD_PROLOG_FAILED;
		}
	} else
		slurm_mutex_unlock(&prolog_mutex);

	if (!(slurmctld_conf.prolog_flags & PROLOG_FLAG_NOHOLD))
		_notify_slurmctld_prolog_fini(req->job_id, rc);

	if (rc == SLURM_SUCCESS) {
		if (slurmctld_conf.prolog_flags & PROLOG_FLAG_CONTAIN)
			_spawn_prolog_stepd(msg);
	} else {
		_launch_job_fail(req->job_id, rc);
		send_registration_msg(rc, false);
	}
}