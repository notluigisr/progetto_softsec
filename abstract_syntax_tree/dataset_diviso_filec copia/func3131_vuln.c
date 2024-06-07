int fit_check_format(const void *fit, ulong size)
{
	int ret;

	
	ret = fdt_check_header(fit);
	if (ret) {
		log_debug("STR",
			  ret);
		return -ENOEXEC;
	}

	if (CONFIG_IS_ENABLED(FIT_FULL_CHECK)) {
		
		if (size == IMAGE_SIZE_INVAL)
			size = fdt_totalsize(fit);
		ret = fdt_check_full(fit, size);

		if (ret) {
			log_debug("STR", ret);
			return -EINVAL;
		}
	}

	
	if (!fdt_getprop(fit, 0, FIT_DESC_PROP, NULL)) {
		log_debug("STR");
		return -ENOMSG;
	}

	if (IMAGE_ENABLE_TIMESTAMP) {
		
		if (!fdt_getprop(fit, 0, FIT_TIMESTAMP_PROP, NULL)) {
			log_debug("STR");
			return -ENODATA;
		}
	}

	
	if (fdt_path_offset(fit, FIT_IMAGES_PATH) < 0) {
		log_debug("STR");
		return -ENOENT;
	}

	return 0;
}