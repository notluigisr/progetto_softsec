void btrfs_put_block_group(struct btrfs_block_group *cache)
{
	if (refcount_dec_and_test(&cache->refs)) {
		WARN_ON(cache->pinned > 0);
		WARN_ON(cache->reserved > 0);

		
		if (WARN_ON(!list_empty(&cache->discard_list)))
			btrfs_discard_cancel_work(&cache->fs_info->discard_ctl,
						  cache);

		
		WARN_ON(!RB_EMPTY_ROOT(&cache->full_stripe_locks_root.root));
		kfree(cache->free_space_ctl);
		kfree(cache);
	}
}