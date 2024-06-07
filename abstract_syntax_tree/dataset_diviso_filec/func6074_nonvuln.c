static int __init apparmor_init(void)
{
	int error;

	if (!apparmor_enabled || !security_module_enable(&apparmor_ops)) {
		aa_info_message("STR");
		apparmor_enabled = 0;
		return 0;
	}

	error = aa_alloc_root_ns();
	if (error) {
		AA_ERROR("STR");
		goto alloc_out;
	}

	error = set_init_cxt();
	if (error) {
		AA_ERROR("STR");
		goto register_security_out;
	}

	error = register_security(&apparmor_ops);
	if (error) {
		AA_ERROR("STR");
		goto set_init_cxt_out;
	}

	
	apparmor_initialized = 1;
	if (aa_g_profile_mode == APPARMOR_COMPLAIN)
		aa_info_message("STR");
	else if (aa_g_profile_mode == APPARMOR_KILL)
		aa_info_message("STR");
	else
		aa_info_message("STR");

	return error;

set_init_cxt_out:
	aa_free_task_context(current->real_cred->security);

register_security_out:
	aa_free_root_ns();

alloc_out:
	aa_destroy_aafs();

	apparmor_enabled = 0;
	return error;
}