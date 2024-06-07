static char *stibp_state(void)
{
	if (spectre_v2_enabled == SPECTRE_V2_IBRS_ENHANCED)
		return "";

	switch (spectre_v2_user) {
	case SPECTRE_V2_USER_NONE:
		return "STR";
	case SPECTRE_V2_USER_STRICT:
		return "STR";
	case SPECTRE_V2_USER_STRICT_PREFERRED:
		return "STR";
	case SPECTRE_V2_USER_PRCTL:
	case SPECTRE_V2_USER_SECCOMP:
		if (static_key_enabled(&switch_to_cond_stibp))
			return "STR";
	}
	return "";
}