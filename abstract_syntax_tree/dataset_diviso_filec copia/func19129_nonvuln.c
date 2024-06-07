static struct bpf_blk *_blk_alloc(void)
{
	struct bpf_blk *blk;

	blk = zmalloc(sizeof(*blk));
	if (blk == NULL)
		return NULL;
	blk->flag_unique = true;
	blk->acc_start = _ACC_STATE_UNDEF;
	blk->acc_end = _ACC_STATE_UNDEF;

	return blk;
}