void elv_unregister(struct elevator_type *e)
{
	
	spin_lock(&elv_list_lock);
	list_del_init(&e->list);
	spin_unlock(&elv_list_lock);

	
	if (e->icq_cache) {
		rcu_barrier();
		kmem_cache_destroy(e->icq_cache);
		e->icq_cache = NULL;
	}
}