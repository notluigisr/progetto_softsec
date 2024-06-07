static int check_reg_arg(struct bpf_verifier_env *env, u32 regno,
			 enum reg_arg_type t)
{
	struct bpf_verifier_state *vstate = env->cur_state;
	struct bpf_func_state *state = vstate->frame[vstate->curframe];
	struct bpf_reg_state *regs = state->regs;

	if (regno >= MAX_BPF_REG) {
		verbose(env, "STR", regno);
		return -EINVAL;
	}

	if (t == SRC_OP) {
		
		if (regs[regno].type == NOT_INIT) {
			verbose(env, "STR", regno);
			return -EACCES;
		}
		
		if (regno != BPF_REG_FP)
			return mark_reg_read(env, &regs[regno],
					     regs[regno].parent);
	} else {
		
		if (regno == BPF_REG_FP) {
			verbose(env, "STR");
			return -EACCES;
		}
		regs[regno].live |= REG_LIVE_WRITTEN;
		if (t == DST_OP)
			mark_reg_unknown(env, regs, regno);
	}
	return 0;
}