static int check_ptr_alignment(struct bpf_verifier_env *env,
			       const struct bpf_reg_state *reg,
			       int off, int size)
{
	bool strict = env->strict_alignment;
	const char *pointer_desc = "";

	switch (reg->type) {
	case PTR_TO_PACKET:
	case PTR_TO_PACKET_META:
		
		return check_pkt_ptr_alignment(env, reg, off, size, strict);
	case PTR_TO_MAP_VALUE:
		pointer_desc = "STR";
		break;
	case PTR_TO_CTX:
		pointer_desc = "STR";
		break;
	case PTR_TO_STACK:
		pointer_desc = "STR";
		break;
	default:
		break;
	}
	return check_generic_ptr_alignment(env, reg, pointer_desc, off, size,
					   strict);
}