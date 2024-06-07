static int get_hstate_idx(int page_size_log)
{
	struct hstate *h = hstate_sizelog(page_size_log);

	if (!h)
		return -1;
	return h - hstates;
}