void setup_new_exec(struct linux_binprm * bprm)
{
	
	bprm->secureexec |= bprm->cap_elevated;

	if (bprm->secureexec) {
		
		current->pdeath_signal = 0;

		
		if (bprm->rlim_stack.rlim_cur > _STK_LIM)
			bprm->rlim_stack.rlim_cur = _STK_LIM;
	}

	arch_pick_mmap_layout(current->mm, &bprm->rlim_stack);

	current->sas_ss_sp = current->sas_ss_size = 0;

	
	if (bprm->interp_flags & BINPRM_FLAGS_ENFORCE_NONDUMP ||
	    !(uid_eq(current_euid(), current_uid()) &&
	      gid_eq(current_egid(), current_gid())))
		set_dumpable(current->mm, suid_dumpable);
	else
		set_dumpable(current->mm, SUID_DUMP_USER);

	arch_setup_new_exec();
	perf_event_exec();
	__set_task_comm(current, kbasename(bprm->filename), true);

	
	current->mm->task_size = TASK_SIZE;

	
	current->self_exec_id++;
	flush_signal_handlers(current, 0);
}