static void umd_cleanup(struct subprocess_info *info)
{
	struct umd_info *umd_info = info->data;

	
	if (info->retval) {
		fput(umd_info->pipe_to_umh);
		fput(umd_info->pipe_from_umh);
		put_pid(umd_info->tgid);
		umd_info->tgid = NULL;
	}
}