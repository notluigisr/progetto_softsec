spectre_v2_user_select_mitigation(enum spectre_v2_mitigation_cmd v2_cmd)
{
	enum spectre_v2_user_mitigation mode = SPECTRE_V2_USER_NONE;
	bool smt_possible = IS_ENABLED(CONFIG_SMP);
	enum spectre_v2_user_cmd cmd;

	if (!boot_cpu_has(X86_FEATURE_IBPB) && !boot_cpu_has(X86_FEATURE_STIBP))
		return;

	if (cpu_smt_control == CPU_SMT_FORCE_DISABLED ||
	    cpu_smt_control == CPU_SMT_NOT_SUPPORTED)
		smt_possible = false;

	cmd = spectre_v2_parse_user_cmdline(v2_cmd);
	switch (cmd) {
	case SPECTRE_V2_USER_CMD_NONE:
		goto set_mode;
	case SPECTRE_V2_USER_CMD_FORCE:
		mode = SPECTRE_V2_USER_STRICT;
		break;
	case SPECTRE_V2_USER_CMD_PRCTL:
	case SPECTRE_V2_USER_CMD_PRCTL_IBPB:
		mode = SPECTRE_V2_USER_PRCTL;
		break;
	case SPECTRE_V2_USER_CMD_AUTO:
	case SPECTRE_V2_USER_CMD_SECCOMP:
	case SPECTRE_V2_USER_CMD_SECCOMP_IBPB:
		if (IS_ENABLED(CONFIG_SECCOMP))
			mode = SPECTRE_V2_USER_SECCOMP;
		else
			mode = SPECTRE_V2_USER_PRCTL;
		break;
	}

	
	if (mode != SPECTRE_V2_USER_STRICT &&
	    boot_cpu_has(X86_FEATURE_AMD_STIBP_ALWAYS_ON))
		mode = SPECTRE_V2_USER_STRICT_PREFERRED;

	
	if (boot_cpu_has(X86_FEATURE_IBPB)) {
		setup_force_cpu_cap(X86_FEATURE_USE_IBPB);

		switch (cmd) {
		case SPECTRE_V2_USER_CMD_FORCE:
		case SPECTRE_V2_USER_CMD_PRCTL_IBPB:
		case SPECTRE_V2_USER_CMD_SECCOMP_IBPB:
			static_branch_enable(&switch_mm_always_ibpb);
			break;
		case SPECTRE_V2_USER_CMD_PRCTL:
		case SPECTRE_V2_USER_CMD_AUTO:
		case SPECTRE_V2_USER_CMD_SECCOMP:
			static_branch_enable(&switch_mm_cond_ibpb);
			break;
		default:
			break;
		}

		pr_info("STR",
			static_key_enabled(&switch_mm_always_ibpb) ?
			"STR");
	}

	
	if (spectre_v2_enabled == SPECTRE_V2_IBRS_ENHANCED)
		return;

	
	if (!smt_possible || !boot_cpu_has(X86_FEATURE_STIBP))
		mode = SPECTRE_V2_USER_NONE;
set_mode:
	spectre_v2_user = mode;
	
	if (smt_possible)
		pr_info("STR", spectre_v2_user_strings[mode]);
}