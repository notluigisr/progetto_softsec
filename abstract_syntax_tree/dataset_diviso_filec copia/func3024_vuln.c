static inline int xsave_state(struct xsave_struct *fx, u64 mask)
{
	u32 lmask = mask;
	u32 hmask = mask >> 32;
	int err = 0;

	
	alternative_input_2(
		"STR"XSAVE,
		"STR"XSAVEOPT,
		X86_FEATURE_XSAVEOPT,
		"STR"XSAVES,
		X86_FEATURE_XSAVES,
		[fx] "STR" (hmask) :
		"STR");
	asm volatile("STR"
		     xstate_fault
		     : "STR" (0)
		     : "STR");

	return err;
}