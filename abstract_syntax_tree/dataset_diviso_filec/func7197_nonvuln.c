static int _activate_check_status(struct crypt_device *cd, const char *name, unsigned reload)
{
	int r;

	if (!name)
		return 0;

	r = dm_status_device(cd, name);

	if (r >= 0 && reload)
		return 0;

	if (r >= 0 || r == -EEXIST) {
		log_err(cd, _("STR"), name);
		return -EEXIST;
	}

	if (r == -ENODEV)
		return 0;

	log_err(cd, _("STR"), name);
	return r;
}