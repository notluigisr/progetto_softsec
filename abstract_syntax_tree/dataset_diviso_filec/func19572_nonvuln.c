void btrfs_wait_space_cache_v1_finished(struct btrfs_block_group *cache,
				struct btrfs_caching_control *caching_ctl)
{
	wait_event(caching_ctl->wait, space_cache_v1_done(cache));
}