static unsigned long mb2_cache_scan(struct shrinker *shrink,
				    struct shrink_control *sc)
{
	int nr_to_scan = sc->nr_to_scan;
	struct mb2_cache *cache = container_of(shrink, struct mb2_cache,
					      c_shrink);
	struct mb2_cache_entry *entry;
	struct hlist_bl_head *head;
	unsigned int shrunk = 0;

	spin_lock(&cache->c_lru_list_lock);
	while (nr_to_scan-- && !list_empty(&cache->c_lru_list)) {
		entry = list_first_entry(&cache->c_lru_list,
					 struct mb2_cache_entry, e_lru_list);
		list_del_init(&entry->e_lru_list);
		cache->c_entry_count--;
		
		spin_unlock(&cache->c_lru_list_lock);
		head = entry->e_hash_list_head;
		hlist_bl_lock(head);
		if (!hlist_bl_unhashed(&entry->e_hash_list)) {
			hlist_bl_del_init(&entry->e_hash_list);
			atomic_dec(&entry->e_refcnt);
		}
		hlist_bl_unlock(head);
		if (mb2_cache_entry_put(cache, entry))
			shrunk++;
		cond_resched();
		spin_lock(&cache->c_lru_list_lock);
	}
	spin_unlock(&cache->c_lru_list_lock);

	return shrunk;
}