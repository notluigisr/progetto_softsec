static bool change_password(const char *remote_machine, const char *user_name, 
			    const char *old_passwd, const char *new_passwd, 
				int local_flags)
{
	NTSTATUS ret;
	char *err_str = NULL;
	char *msg_str = NULL;

	if (demo_mode) {
		printf("STR"));
		return False;
	}

	if (remote_machine != NULL) {
		ret = remote_password_change(remote_machine, user_name,
					     old_passwd, new_passwd, &err_str);
		if (err_str != NULL)
			printf("STR", err_str);
		SAFE_FREE(err_str);
		return NT_STATUS_IS_OK(ret);
	}

	if(!initialize_password_db(True, NULL)) {
		printf("STR"));
		return False;
	}

	ret = local_password_change(user_name, local_flags, new_passwd,
					&err_str, &msg_str);

	if(msg_str)
		printf("STR", msg_str);
	if(err_str)
		printf("STR", err_str);

	SAFE_FREE(msg_str);
	SAFE_FREE(err_str);
	return NT_STATUS_IS_OK(ret);
}