static void put_pi_state(struct futex_pi_state *pi_state)
{
	if (!pi_state)
		return;

	if (!refcount_dec_and_test(&pi_state->refcount))
		return;

	
	if (pi_state->owner) {
		struct task_struct *owner;

		raw_spin_lock_irq(&pi_state->pi_mutex.wait_lock);
		owner = pi_state->owner;
		if (owner) {
			raw_spin_lock(&owner->pi_lock);
			list_del_init(&pi_state->list);
			raw_spin_unlock(&owner->pi_lock);
		}
		rt_mutex_proxy_unlock(&pi_state->pi_mutex, owner);
		raw_spin_unlock_irq(&pi_state->pi_mutex.wait_lock);
	}

	if (current->pi_state_cache) {
		kfree(pi_state);
	} else {
		
		pi_state->owner = NULL;
		refcount_set(&pi_state->refcount, 1);
		current->pi_state_cache = pi_state;
	}
}