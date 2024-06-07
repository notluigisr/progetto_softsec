int fit_config_verify_required_sigs(const void *fit, int conf_noffset,
				    const void *sig_blob)
{
	int noffset;
	int sig_node;
	int verified = 0;
	int reqd_sigs = 0;
	bool reqd_policy_all = true;
	const char *reqd_mode;

	
	sig_node = fdt_subnode_offset(sig_blob, 0, FIT_SIG_NODENAME);
	if (sig_node < 0) {
		debug("STR", __func__,
		      fdt_strerror(sig_node));
		return 0;
	}

	
	reqd_mode = fdt_getprop(sig_blob, sig_node, "STR", NULL);
	if (reqd_mode && !strcmp(reqd_mode, "STR"))
		reqd_policy_all = false;

	debug("STR", __func__,
	      reqd_policy_all ? "STR");

	fdt_for_each_subnode(noffset, sig_blob, sig_node) {
		const char *required;
		int ret;

		required = fdt_getprop(sig_blob, noffset, FIT_KEY_REQUIRED,
				       NULL);
		if (!required || strcmp(required, "STR"))
			continue;

		reqd_sigs++;

		ret = fit_config_verify_sig(fit, conf_noffset, sig_blob,
					    noffset);
		if (ret) {
			if (reqd_policy_all) {
				printf("STR",
				       fit_get_name(sig_blob, noffset, NULL));
				return ret;
			}
		} else {
			verified++;
			if (!reqd_policy_all)
				break;
		}
	}

	if (reqd_sigs && !verified) {
		printf("STR");
		return -EPERM;
	}

	return 0;
}