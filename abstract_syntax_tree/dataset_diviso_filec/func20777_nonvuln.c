static void skip_metadata(struct pstore *ps)
{
	uint32_t stride = ps->exceptions_per_area + 1;
	chunk_t next_free = ps->next_free;
	if (sector_div(next_free, stride) == NUM_SNAPSHOT_HDR_CHUNKS)
		ps->next_free++;
}