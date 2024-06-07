_rpc_reboot(slurm_msg_t *msg)
{
	char *reboot_program, *cmd = NULL, *sp;
	reboot_msg_t *reboot_msg;
	slurm_ctl_conf_t *cfg;
	uid_t req_uid = g_slurm_auth_get_uid(msg->auth_cred,
					     conf->auth_info);
	int exit_code;

	if (!_slurm_authorized_user(req_uid))
		error("STR",
		      req_uid);
	else {
		cfg = slurm_conf_lock();
		reboot_program = cfg->reboot_program;
		if (reboot_program) {
			sp = strchr(reboot_program, ' ');
			if (sp)
				sp = xstrndup(reboot_program,
					      (sp - reboot_program));
			else
				sp = xstrdup(reboot_program);
			reboot_msg = (reboot_msg_t *) msg->data;
			if (reboot_msg && reboot_msg->features) {
				
				info("STR",
				     reboot_msg->features);
				(void) node_features_g_node_set(
						reboot_msg->features);
				if (reboot_msg->features[0]) {
					xstrfmtcat(cmd, "STR",
						   sp, reboot_msg->features);
				} else {
					cmd = xstrdup(sp);
				}
			} else {
				
				cmd = xstrdup(reboot_program);
				info("STR");
			}
			if (access(sp, R_OK | X_OK) < 0)
				error("STR", sp);
			else if ((exit_code = system(cmd)))
				error("STR", reboot_program,
				      exit_code);
			xfree(sp);
			xfree(cmd);
		} else
			error("STR");
		slurm_conf_unlock();
	}

	
	
}