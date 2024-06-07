static struct bpf_blk *_gen_bpf_chain_lvl_res(struct bpf_state *state,
					      const struct db_sys_list *sys,
					      struct bpf_blk *blk,
					      const struct bpf_jump *nxt_jump)
{
	int rc;
	unsigned int iter;
	struct bpf_blk *b_new;
	struct bpf_instr *i_iter;
	struct db_arg_chain_tree *node;

	if (blk->flag_hash)
		return blk;

	
	for (iter = 0; iter < blk->blk_cnt; iter++) {
		i_iter = &blk->blks[iter];
		switch (i_iter->jt.type) {
		case TGT_NONE:
		case TGT_IMM:
		case TGT_PTR_HSH:
			
			break;
		case TGT_PTR_BLK:
			b_new = _gen_bpf_chain_lvl_res(state, sys,
						       i_iter->jt.tgt.blk,
						       nxt_jump);
			if (b_new == NULL)
				return NULL;
			i_iter->jt = _BPF_JMP_HSH(b_new->hash);
			break;
		case TGT_PTR_DB:
			node = (struct db_arg_chain_tree *)i_iter->jt.tgt.db;
			b_new = _gen_bpf_chain(state, sys, node,
					       nxt_jump, &blk->acc_start);
			if (b_new == NULL)
				return NULL;
			i_iter->jt = _BPF_JMP_HSH(b_new->hash);
			break;
		default:
			
			return NULL;
		}
		switch (i_iter->jf.type) {
		case TGT_NONE:
		case TGT_IMM:
		case TGT_PTR_HSH:
			
			break;
		case TGT_PTR_BLK:
			b_new = _gen_bpf_chain_lvl_res(state, sys,
						       i_iter->jf.tgt.blk,
						       nxt_jump);
			if (b_new == NULL)
				return NULL;
			i_iter->jf = _BPF_JMP_HSH(b_new->hash);
			break;
		case TGT_PTR_DB:
			node = (struct db_arg_chain_tree *)i_iter->jf.tgt.db;
			b_new = _gen_bpf_chain(state, sys, node,
					       nxt_jump, &blk->acc_start);
			if (b_new == NULL)
				return NULL;
			i_iter->jf = _BPF_JMP_HSH(b_new->hash);
			break;
		default:
			
			return NULL;
		}
		switch (i_iter->k.type) {
		case TGT_NONE:
		case TGT_K:
		case TGT_PTR_HSH:
			
			break;
		default:
			
			return NULL;
		}
	}

	
	rc = _hsh_add(state, &blk, 0);
	if (rc < 0)
		return NULL;

	return blk;
}