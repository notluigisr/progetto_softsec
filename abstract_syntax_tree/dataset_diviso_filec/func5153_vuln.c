static int bprm_execve(struct linux_binprm *bprm,
		       int fd, struct filename *filename, int flags)
{
	struct file *file;
	struct files_struct *displaced;
	int retval;

	retval = unshare_files(&displaced);
	if (retval)
		return retval;

	retval = prepare_bprm_creds(bprm);
	if (retval)
		goto out_files;

	check_unsafe_exec(bprm);
	current->in_execve = 1;

	file = do_open_execat(fd, filename, flags);
	retval = PTR_ERR(file);
	if (IS_ERR(file))
		goto out_unmark;

	sched_exec();

	bprm->file = file;
	
	if (bprm->fdpath &&
	    close_on_exec(fd, rcu_dereference_raw(current->files->fdt)))
		bprm->interp_flags |= BINPRM_FLAGS_PATH_INACCESSIBLE;

	
	retval = security_bprm_creds_for_exec(bprm);
	if (retval)
		goto out;

	retval = exec_binprm(bprm);
	if (retval < 0)
		goto out;

	
	current->fs->in_exec = 0;
	current->in_execve = 0;
	rseq_execve(current);
	acct_update_integrals(current);
	task_numa_free(current, false);
	if (displaced)
		put_files_struct(displaced);
	return retval;

out:
	
	if (bprm->point_of_no_return && !fatal_signal_pending(current))
		force_sigsegv(SIGSEGV);

out_unmark:
	current->fs->in_exec = 0;
	current->in_execve = 0;

out_files:
	if (displaced)
		reset_files_struct(displaced);

	return retval;
}