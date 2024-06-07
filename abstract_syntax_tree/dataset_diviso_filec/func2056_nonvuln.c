static dma_addr_t pq_get_src(struct ioat_raw_descriptor *descs[2], int idx)
{
	struct ioat_raw_descriptor *raw = descs[pq_idx_to_desc >> idx & 1];

	return raw->field[pq_idx_to_field[idx]];
}