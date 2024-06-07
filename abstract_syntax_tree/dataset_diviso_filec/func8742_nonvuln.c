static int check_kfunc_call(struct bpf_verifier_env *env, struct bpf_insn *insn)
{
	const struct btf_type *t, *func, *func_proto, *ptr_type;
	struct bpf_reg_state *regs = cur_regs(env);
	const char *func_name, *ptr_type_name;
	u32 i, nargs, func_id, ptr_type_id;
	const struct btf_param *args;
	int err;

	func_id = insn->imm;
	func = btf_type_by_id(btf_vmlinux, func_id);
	func_name = btf_name_by_offset(btf_vmlinux, func->name_off);
	func_proto = btf_type_by_id(btf_vmlinux, func->type);

	if (!env->ops->check_kfunc_call ||
	    !env->ops->check_kfunc_call(func_id)) {
		verbose(env, "STR",
			func_name);
		return -EACCES;
	}

	
	err = btf_check_kfunc_arg_match(env, btf_vmlinux, func_id, regs);
	if (err)
		return err;

	for (i = 0; i < CALLER_SAVED_REGS; i++)
		mark_reg_not_init(env, regs, caller_saved[i]);

	
	t = btf_type_skip_modifiers(btf_vmlinux, func_proto->type, NULL);
	if (btf_type_is_scalar(t)) {
		mark_reg_unknown(env, regs, BPF_REG_0);
		mark_btf_func_reg_size(env, BPF_REG_0, t->size);
	} else if (btf_type_is_ptr(t)) {
		ptr_type = btf_type_skip_modifiers(btf_vmlinux, t->type,
						   &ptr_type_id);
		if (!btf_type_is_struct(ptr_type)) {
			ptr_type_name = btf_name_by_offset(btf_vmlinux,
							   ptr_type->name_off);
			verbose(env, "STR",
				func_name, btf_type_str(ptr_type),
				ptr_type_name);
			return -EINVAL;
		}
		mark_reg_known_zero(env, regs, BPF_REG_0);
		regs[BPF_REG_0].btf = btf_vmlinux;
		regs[BPF_REG_0].type = PTR_TO_BTF_ID;
		regs[BPF_REG_0].btf_id = ptr_type_id;
		mark_btf_func_reg_size(env, BPF_REG_0, sizeof(void *));
	} 

	nargs = btf_type_vlen(func_proto);
	args = (const struct btf_param *)(func_proto + 1);
	for (i = 0; i < nargs; i++) {
		u32 regno = i + 1;

		t = btf_type_skip_modifiers(btf_vmlinux, args[i].type, NULL);
		if (btf_type_is_ptr(t))
			mark_btf_func_reg_size(env, regno, sizeof(void *));
		else
			
			mark_btf_func_reg_size(env, regno, t->size);
	}

	return 0;
}