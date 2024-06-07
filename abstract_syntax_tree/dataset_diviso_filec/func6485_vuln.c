static void __reg_combine_64_into_32(struct bpf_reg_state *reg)
{
	__mark_reg32_unbounded(reg);

	if (__reg64_bound_s32(reg->smin_value) && __reg64_bound_s32(reg->smax_value)) {
		reg->s32_min_value = (s32)reg->smin_value;
		reg->s32_max_value = (s32)reg->smax_value;
	}
	if (__reg64_bound_u32(reg->umin_value))
		reg->u32_min_value = (u32)reg->umin_value;
	if (__reg64_bound_u32(reg->umax_value))
		reg->u32_max_value = (u32)reg->umax_value;

	
	__reg_deduce_bounds(reg);
	__reg_bound_offset(reg);
	__update_reg_bounds(reg);
}