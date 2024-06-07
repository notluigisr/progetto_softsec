int crypt_reencrypt_run(
	struct crypt_device *cd,
	int (*progress)(uint64_t size, uint64_t offset, void *usrptr),
	void *usrptr)
{
	int r;
	crypt_reencrypt_info ri;
	struct luks2_hdr *hdr;
	struct luks2_reencrypt *rh;
	reenc_status_t rs;
	bool quit = false;

	if (onlyLUKS2mask(cd, CRYPT_REQUIREMENT_ONLINE_REENCRYPT))
		return -EINVAL;

	hdr = crypt_get_hdr(cd, CRYPT_LUKS2);

	ri = LUKS2_reencrypt_status(hdr);
	if (ri > CRYPT_REENCRYPT_CLEAN) {
		log_err(cd, _("STR"));
		return -EINVAL;
	}

	rh = crypt_get_luks2_reencrypt(cd);
	if (!rh || (!rh->reenc_lock && crypt_metadata_locking_enabled())) {
		log_err(cd, _("STR"));
		return -EINVAL;
	}

	log_dbg(cd, "STR");

	if (rh->online && reencrypt_init_device_stack(cd, rh)) {
		log_err(cd, _("STR"));
		return -EINVAL;
	}

	log_dbg(cd, "STR" PRIu64, rh->progress, rh->device_size);

	rs = REENC_OK;

	while (!quit && (rh->device_size > rh->progress)) {
		rs = reencrypt_step(cd, hdr, rh, rh->device_size, rh->online);
		if (rs != REENC_OK)
			break;

		log_dbg(cd, "STR" PRIu64, rh->progress, rh->device_size);
		if (progress && progress(rh->device_size, rh->progress, usrptr))
			quit = true;

		r = reencrypt_context_update(cd, rh);
		if (r) {
			log_err(cd, _("STR"));
			rs = REENC_ERR;
			break;
		}

		log_dbg(cd, "STR", rh->offset);
		log_dbg(cd, "STR", rh->length);
	}

	r = reencrypt_teardown(cd, hdr, rh, rs, quit, progress, usrptr);
	return r;
}