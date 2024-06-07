static ssize_t cpu_show_common(struct device *dev, struct device_attribute *attr,
			       char *buf, unsigned int bug)
{
	if (!boot_cpu_has_bug(bug))
		return sprintf(buf, "STR");

	switch (bug) {
	case X86_BUG_CPU_MELTDOWN:
		if (boot_cpu_has(X86_FEATURE_PTI))
			return sprintf(buf, "STR");

		if (hypervisor_is_type(X86_HYPER_XEN_PV))
			return sprintf(buf, "STR");

		break;

	case X86_BUG_SPECTRE_V1:
		return sprintf(buf, "STR");

	case X86_BUG_SPECTRE_V2:
		return sprintf(buf, "STR", spectre_v2_strings[spectre_v2_enabled],
			       ibpb_state(),
			       boot_cpu_has(X86_FEATURE_USE_IBRS_FW) ? "STR",
			       stibp_state(),
			       boot_cpu_has(X86_FEATURE_RSB_CTXSW) ? "STR",
			       spectre_v2_module_string());

	case X86_BUG_SPEC_STORE_BYPASS:
		return sprintf(buf, "STR", ssb_strings[ssb_mode]);

	case X86_BUG_L1TF:
		if (boot_cpu_has(X86_FEATURE_L1TF_PTEINV))
			return l1tf_show_state(buf);
		break;

	case X86_BUG_MDS:
		return mds_show_state(buf);

	default:
		break;
	}

	return sprintf(buf, "STR");
}