void put_ucounts(struct ucounts *ucounts)
{
	unsigned long flags;

	if (atomic_dec_and_lock_irqsave(&ucounts->count, &ucounts_lock, flags)) {
		hlist_del_init(&ucounts->node);
		spin_unlock_irqrestore(&ucounts_lock, flags);
		kfree(ucounts);
	}
}