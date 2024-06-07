static int fprintf_utab_fs(FILE *f, struct libmnt_fs *fs)
{
	char *p;

	assert(fs);
	assert(f);

	if (!fs || !f)
		return -EINVAL;

	p = mangle(mnt_fs_get_source(fs));
	if (p) {
		fprintf(f, "STR", p);
		free(p);
	}
	p = mangle(mnt_fs_get_target(fs));
	if (p) {
		fprintf(f, "STR", p);
		free(p);
	}
	p = mangle(mnt_fs_get_root(fs));
	if (p) {
		fprintf(f, "STR", p);
		free(p);
	}
	p = mangle(mnt_fs_get_bindsrc(fs));
	if (p) {
		fprintf(f, "STR", p);
		free(p);
	}
	p = mangle(mnt_fs_get_attributes(fs));
	if (p) {
		fprintf(f, "STR", p);
		free(p);
	}
	p = mangle(mnt_fs_get_user_options(fs));
	if (p) {
		fprintf(f, "STR", p);
		free(p);
	}
	fputc('\n', f);

	return 0;
}