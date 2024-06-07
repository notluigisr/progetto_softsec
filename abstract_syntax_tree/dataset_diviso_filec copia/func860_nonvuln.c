static int invoke_bpf_prog(const struct btf_func_model *m, u8 **pprog,
			   struct bpf_prog *p, int stack_size, bool mod_ret)
{
	u8 *prog = *pprog;
	u8 *jmp_insn;
	int cnt = 0;

	
	emit_mov_imm64(&prog, BPF_REG_1, (long) p >> 32, (u32) (long) p);
	if (emit_call(&prog,
		      p->aux->sleepable ? __bpf_prog_enter_sleepable :
		      __bpf_prog_enter, prog))
			return -EINVAL;
	
	emit_mov_reg(&prog, true, BPF_REG_6, BPF_REG_0);

	
	EMIT3(0x48, 0x85, 0xC0);  
	
	jmp_insn = prog;
	emit_nops(&prog, 2);

	
	EMIT4(0x48, 0x8D, 0x7D, -stack_size);
	
	if (!p->jited)
		emit_mov_imm64(&prog, BPF_REG_2,
			       (long) p->insnsi >> 32,
			       (u32) (long) p->insnsi);
	
	if (emit_call(&prog, p->bpf_func, prog))
		return -EINVAL;

	
	if (mod_ret)
		emit_stx(&prog, BPF_DW, BPF_REG_FP, BPF_REG_0, -8);

	
	jmp_insn[0] = X86_JE;
	jmp_insn[1] = prog - jmp_insn - 2;

	
	emit_mov_imm64(&prog, BPF_REG_1, (long) p >> 32, (u32) (long) p);
	
	emit_mov_reg(&prog, true, BPF_REG_2, BPF_REG_6);
	if (emit_call(&prog,
		      p->aux->sleepable ? __bpf_prog_exit_sleepable :
		      __bpf_prog_exit, prog))
			return -EINVAL;

	*pprog = prog;
	return 0;
}