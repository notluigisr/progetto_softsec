static bool __init xen_check_xsave(void)
{
	unsigned int cx, xsave_mask;

	cx = cpuid_ecx(1);

	xsave_mask = (1 << (X86_FEATURE_XSAVE % 32)) |
		     (1 << (X86_FEATURE_OSXSAVE % 32));

	
	return (cx & xsave_mask) == xsave_mask;
}