static void unqueue_me_pi(struct futex_q *q)
{
	WARN_ON(plist_node_empty(&q->list));
	plist_del(&q->list, &q->list.plist);

	BUG_ON(!q->pi_state);
	free_pi_state(q->pi_state);
	q->pi_state = NULL;

	spin_unlock(q->lock_ptr);

	drop_futex_key_refs(&q->key);
}