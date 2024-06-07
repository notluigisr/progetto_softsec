static inline int xrstor_state(struct xsave_struct *fx, u64 mask)
{
	int err = 0;
	u32 lmask = mask;
	u32 hmask = mask >> 32;

	
	alternative_input(
		"STR" XRSTOR,
		XRSTORS,
		X86_FEATURE_XSAVES,
		"STR" (hmask)
		: "STR");

	asm volatile("STR"
		     xstate_fault
		     : "STR" (0)
		     : "STR");

	return err;
}