static int opt_subreg_zext_lo32_rnd_hi32(struct bpf_verifier_env *env,
					 const union bpf_attr *attr)
{
	struct bpf_insn *patch, zext_patch[2], rnd_hi32_patch[4];
	struct bpf_insn_aux_data *aux = env->insn_aux_data;
	int i, patch_len, delta = 0, len = env->prog->len;
	struct bpf_insn *insns = env->prog->insnsi;
	struct bpf_prog *new_prog;
	bool rnd_hi32;

	rnd_hi32 = attr->prog_flags & BPF_F_TEST_RND_HI32;
	zext_patch[1] = BPF_ZEXT_REG(0);
	rnd_hi32_patch[1] = BPF_ALU64_IMM(BPF_MOV, BPF_REG_AX, 0);
	rnd_hi32_patch[2] = BPF_ALU64_IMM(BPF_LSH, BPF_REG_AX, 32);
	rnd_hi32_patch[3] = BPF_ALU64_REG(BPF_OR, 0, BPF_REG_AX);
	for (i = 0; i < len; i++) {
		int adj_idx = i + delta;
		struct bpf_insn insn;

		insn = insns[adj_idx];
		if (!aux[adj_idx].zext_dst) {
			u8 code, class;
			u32 imm_rnd;

			if (!rnd_hi32)
				continue;

			code = insn.code;
			class = BPF_CLASS(code);
			if (insn_no_def(&insn))
				continue;

			
			if (is_reg64(env, &insn, insn.dst_reg, NULL, DST_OP)) {
				if (class == BPF_LD &&
				    BPF_MODE(code) == BPF_IMM)
					i++;
				continue;
			}

			
			if (class == BPF_LDX &&
			    aux[adj_idx].ptr_type == PTR_TO_CTX)
				continue;

			imm_rnd = get_random_int();
			rnd_hi32_patch[0] = insn;
			rnd_hi32_patch[1].imm = imm_rnd;
			rnd_hi32_patch[3].dst_reg = insn.dst_reg;
			patch = rnd_hi32_patch;
			patch_len = 4;
			goto apply_patch_buffer;
		}

		if (!bpf_jit_needs_zext())
			continue;

		zext_patch[0] = insn;
		zext_patch[1].dst_reg = insn.dst_reg;
		zext_patch[1].src_reg = insn.dst_reg;
		patch = zext_patch;
		patch_len = 2;
apply_patch_buffer:
		new_prog = bpf_patch_insn_data(env, adj_idx, patch, patch_len);
		if (!new_prog)
			return -ENOMEM;
		env->prog = new_prog;
		insns = new_prog->insnsi;
		aux = env->insn_aux_data;
		delta += patch_len - 1;
	}

	return 0;
}