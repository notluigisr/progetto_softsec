int mnt_fs_set_source(struct libmnt_fs *fs, const char *source)
{
	char *p = NULL;
	int rc;

	if (!fs)
		return -EINVAL;

	if (source) {
		p = strdup(source);
		if (!p)
			return -ENOMEM;
	}

	rc = __mnt_fs_set_source_ptr(fs, p);
	if (rc)
		free(p);
	return rc;
}