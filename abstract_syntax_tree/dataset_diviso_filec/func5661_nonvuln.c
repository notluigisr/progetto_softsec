static void rsync_panic_handler(UNUSED(int whatsig))
{
	char cmd_buf[300];
	int ret, pid_int = getpid();

	snprintf(cmd_buf, sizeof cmd_buf, get_panic_action(), pid_int, pid_int);

	
	ret = shell_exec(cmd_buf);
	if (ret)
		_exit(ret);
}