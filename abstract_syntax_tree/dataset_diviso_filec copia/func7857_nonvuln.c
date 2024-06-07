static void pq_set_src(struct ioat_raw_descriptor *descs[2],
		       dma_addr_t addr, u32 offset, u8 coef, int idx)
{
	struct ioat_pq_descriptor *pq = (struct ioat_pq_descriptor *) descs[0];
	struct ioat_raw_descriptor *raw = descs[pq_idx_to_desc >> idx & 1];

	raw->field[pq_idx_to_field[idx]] = addr + offset;
	pq->coef[idx] = coef;
}