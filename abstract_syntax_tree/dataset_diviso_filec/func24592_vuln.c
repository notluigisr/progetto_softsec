void mm_release(struct task_struct *tsk, struct mm_struct *mm)
{
	struct completion *vfork_done = tsk->vfork_done;

	
	deactivate_mm(tsk, mm);

	
	if (vfork_done) {
		tsk->vfork_done = NULL;
		complete(vfork_done);
	}

	
	if (tsk->clear_child_tid
	    && !(tsk->flags & PF_SIGNALED)
	    && atomic_read(&mm->mm_users) > 1) {
		u32 __user * tidptr = tsk->clear_child_tid;
		tsk->clear_child_tid = NULL;

		
		put_user(0, tidptr);
		sys_futex(tidptr, FUTEX_WAKE, 1, NULL, NULL, 0);
	}
}