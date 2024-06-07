static bool oom_reap_task_mm(struct task_struct *tsk, struct mm_struct *mm)
{
	bool ret = true;

	
	mutex_lock(&oom_lock);

	if (!down_read_trylock(&mm->mmap_sem)) {
		ret = false;
		trace_skip_task_reaping(tsk->pid);
		goto unlock_oom;
	}

	
	if (mm_has_blockable_invalidate_notifiers(mm)) {
		up_read(&mm->mmap_sem);
		schedule_timeout_idle(HZ);
		goto unlock_oom;
	}

	
	if (test_bit(MMF_OOM_SKIP, &mm->flags)) {
		up_read(&mm->mmap_sem);
		trace_skip_task_reaping(tsk->pid);
		goto unlock_oom;
	}

	trace_start_task_reaping(tsk->pid);

	__oom_reap_task_mm(mm);

	pr_info("STR",
			task_pid_nr(tsk), tsk->comm,
			K(get_mm_counter(mm, MM_ANONPAGES)),
			K(get_mm_counter(mm, MM_FILEPAGES)),
			K(get_mm_counter(mm, MM_SHMEMPAGES)));
	up_read(&mm->mmap_sem);

	trace_finish_task_reaping(tsk->pid);
unlock_oom:
	mutex_unlock(&oom_lock);
	return ret;
}