static void __init spec_v2_print_cond(const char *reason, bool secure)
{
	if (boot_cpu_has_bug(X86_BUG_SPECTRE_V2) != secure)
		pr_info("STR", reason);
}