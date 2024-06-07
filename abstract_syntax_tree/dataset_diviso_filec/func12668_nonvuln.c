static struct bpf_blk *_hsh_find(const struct bpf_state *state, uint64_t h_val)
{
	struct bpf_hash_bkt *h_iter;

	h_iter = _hsh_find_bkt(state, h_val);
	if (h_iter == NULL)
		return NULL;
	return h_iter->blk;
}