void psi_task_switch(struct task_struct *prev, struct task_struct *next,
		     bool sleep)
{
	struct psi_group *group, *common = NULL;
	int cpu = task_cpu(prev);
	void *iter;
	u64 now = cpu_clock(cpu);

	if (next->pid) {
		bool identical_state;

		psi_flags_change(next, 0, TSK_ONCPU);
		
		identical_state = prev->psi_flags == next->psi_flags;
		iter = NULL;
		while ((group = iterate_groups(next, &iter))) {
			if (identical_state &&
			    per_cpu_ptr(group->pcpu, cpu)->tasks[NR_ONCPU]) {
				common = group;
				break;
			}

			psi_group_change(group, cpu, 0, TSK_ONCPU, now, true);
		}
	}

	if (prev->pid) {
		int clear = TSK_ONCPU, set = 0;

		
		if (sleep) {
			clear |= TSK_RUNNING;
			if (prev->in_memstall)
				clear |= TSK_MEMSTALL_RUNNING;
			if (prev->in_iowait)
				set |= TSK_IOWAIT;
		}

		psi_flags_change(prev, clear, set);

		iter = NULL;
		while ((group = iterate_groups(prev, &iter)) && group != common)
			psi_group_change(group, cpu, clear, set, now, true);

		
		if (sleep) {
			clear &= ~TSK_ONCPU;
			for (; group; group = iterate_groups(prev, &iter))
				psi_group_change(group, cpu, clear, set, now, true);
		}
	}
}