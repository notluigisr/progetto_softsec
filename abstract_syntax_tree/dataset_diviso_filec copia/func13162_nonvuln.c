	__releases(q->lock_ptr)
{
	__unqueue_futex(q);

	BUG_ON(!q->pi_state);
	free_pi_state(q->pi_state);
	q->pi_state = NULL;

	spin_unlock(q->lock_ptr);
}