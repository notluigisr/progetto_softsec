__rtrs_get_permit(struct rtrs_clt_sess *clt, enum rtrs_clt_con_type con_type)
{
	size_t max_depth = clt->queue_depth;
	struct rtrs_permit *permit;
	int bit;

	
	do {
		bit = find_first_zero_bit(clt->permits_map, max_depth);
		if (bit >= max_depth)
			return NULL;
	} while (test_and_set_bit_lock(bit, clt->permits_map));

	permit = get_permit(clt, bit);
	WARN_ON(permit->mem_id != bit);
	permit->cpu_id = raw_smp_processor_id();
	permit->con_type = con_type;

	return permit;
}