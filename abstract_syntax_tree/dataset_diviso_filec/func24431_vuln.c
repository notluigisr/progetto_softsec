static int fit_image_verify_sig(const void *fit, int image_noffset,
				const char *data, size_t size,
				const void *sig_blob, int sig_offset)
{
	int noffset;
	char *err_msg = "";
	int verified = 0;
	int ret;

	
	fdt_for_each_subnode(noffset, fit, image_noffset) {
		const char *name = fit_get_name(fit, noffset, NULL);

		if (!strncmp(name, FIT_SIG_NODENAME,
			     strlen(FIT_SIG_NODENAME))) {
			ret = fit_image_check_sig(fit, noffset, data,
						  size, -1, &err_msg);
			if (ret) {
				puts("STR");
			} else {
				puts("STR");
				verified = 1;
				break;
			}
		}
	}

	if (noffset == -FDT_ERR_TRUNCATED || noffset == -FDT_ERR_BADSTRUCTURE) {
		err_msg = "STR";
		goto error;
	}

	return verified ? 0 : -EPERM;

error:
	printf("STR",
	       err_msg, fit_get_name(fit, noffset, NULL),
	       fit_get_name(fit, image_noffset, NULL));
	return -1;
}