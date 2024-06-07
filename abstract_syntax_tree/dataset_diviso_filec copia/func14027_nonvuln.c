static struct bpf_blk *_hsh_remove(struct bpf_state *state, uint64_t h_val)
{
	unsigned int bkt = h_val & _BPF_HASH_MASK;
	struct bpf_blk *blk;
	struct bpf_hash_bkt *h_iter, *h_prev = NULL;

	h_iter = state->htbl[bkt];
	while (h_iter != NULL) {
		if (h_iter->blk->hash == h_val) {
			if (h_prev != NULL)
				h_prev->next = h_iter->next;
			else
				state->htbl[bkt] = h_iter->next;
			blk = h_iter->blk;
			free(h_iter);
			return blk;
		}
		h_prev = h_iter;
		h_iter =  h_iter->next;
	}

	return NULL;
}