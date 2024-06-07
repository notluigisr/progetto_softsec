static __always_inline void __speculation_ctrl_update(unsigned long tifp,
						      unsigned long tifn)
{
	unsigned long tif_diff = tifp ^ tifn;
	u64 msr = x86_spec_ctrl_base;
	bool updmsr = false;

	lockdep_assert_irqs_disabled();

	
	if (tif_diff & _TIF_SSBD) {
		if (static_cpu_has(X86_FEATURE_VIRT_SSBD)) {
			amd_set_ssb_virt_state(tifn);
		} else if (static_cpu_has(X86_FEATURE_LS_CFG_SSBD)) {
			amd_set_core_ssb_state(tifn);
		} else if (static_cpu_has(X86_FEATURE_SPEC_CTRL_SSBD) ||
			   static_cpu_has(X86_FEATURE_AMD_SSBD)) {
			msr |= ssbd_tif_to_spec_ctrl(tifn);
			updmsr  = true;
		}
	}

	
	if (IS_ENABLED(CONFIG_SMP) &&
	    static_branch_unlikely(&switch_to_cond_stibp)) {
		updmsr |= !!(tif_diff & _TIF_SPEC_IB);
		msr |= stibp_tif_to_spec_ctrl(tifn);
	}

	if (updmsr)
		wrmsrl(MSR_IA32_SPEC_CTRL, msr);
}