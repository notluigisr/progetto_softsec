static int lstat_cache(struct cache_def *cache, const char *name, int len,
		       int track_flags, int prefix_len_stat_func)
{
	int flags;
	(void)lstat_cache_matchlen(cache, name, len, &flags, track_flags,
			prefix_len_stat_func);
	return flags;
}