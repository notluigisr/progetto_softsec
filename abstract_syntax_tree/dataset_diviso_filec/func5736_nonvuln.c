static u32 psi_group_change(struct psi_group *group, int cpu,
			    unsigned int clear, unsigned int set)
{
	struct psi_group_cpu *groupc;
	unsigned int t, m;
	enum psi_states s;
	u32 state_mask = 0;

	groupc = per_cpu_ptr(group->pcpu, cpu);

	
	write_seqcount_begin(&groupc->seq);

	record_times(groupc, cpu, false);

	for (t = 0, m = clear; m; m &= ~(1 << t), t++) {
		if (!(m & (1 << t)))
			continue;
		if (groupc->tasks[t] == 0 && !psi_bug) {
			printk_deferred(KERN_ERR "STR",
					cpu, t, groupc->tasks[0],
					groupc->tasks[1], groupc->tasks[2],
					clear, set);
			psi_bug = 1;
		}
		groupc->tasks[t]--;
	}

	for (t = 0; set; set &= ~(1 << t), t++)
		if (set & (1 << t))
			groupc->tasks[t]++;

	
	for (s = 0; s < NR_PSI_STATES; s++) {
		if (test_state(groupc->tasks, s))
			state_mask |= (1 << s);
	}
	groupc->state_mask = state_mask;

	write_seqcount_end(&groupc->seq);

	return state_mask;
}