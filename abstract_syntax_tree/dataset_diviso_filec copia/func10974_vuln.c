static void psi_trigger_destroy(struct kref *ref)
{
	struct psi_trigger *t = container_of(ref, struct psi_trigger, refcount);
	struct psi_group *group = t->group;
	struct task_struct *task_to_destroy = NULL;

	if (static_branch_likely(&psi_disabled))
		return;

	
	wake_up_interruptible(&t->event_wait);

	mutex_lock(&group->trigger_lock);

	if (!list_empty(&t->node)) {
		struct psi_trigger *tmp;
		u64 period = ULLONG_MAX;

		list_del(&t->node);
		group->nr_triggers[t->state]--;
		if (!group->nr_triggers[t->state])
			group->poll_states &= ~(1 << t->state);
		
		list_for_each_entry(tmp, &group->triggers, node)
			period = min(period, div_u64(tmp->win.size,
					UPDATES_PER_WINDOW));
		group->poll_min_period = period;
		
		if (group->poll_states == 0) {
			group->polling_until = 0;
			task_to_destroy = rcu_dereference_protected(
					group->poll_task,
					lockdep_is_held(&group->trigger_lock));
			rcu_assign_pointer(group->poll_task, NULL);
			del_timer(&group->poll_timer);
		}
	}

	mutex_unlock(&group->trigger_lock);

	
	synchronize_rcu();
	
	if (task_to_destroy) {
		
		kthread_stop(task_to_destroy);
	}
	kfree(t);
}