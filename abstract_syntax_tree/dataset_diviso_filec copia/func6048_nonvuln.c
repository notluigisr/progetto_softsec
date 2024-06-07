static int sort_key_cmp(MI_SORT_PARAM *sort_param, const void *a,
			const void *b)
{
  uint not_used[2];
  return (ha_key_cmp(sort_param->seg, *((uchar**) a), *((uchar**) b),
		     USE_WHOLE_KEY, SEARCH_SAME, not_used));
} 