void load_cgroup(const char *fname) {
	if (!fname)
		return;

	FILE *fp = fopen(fname, "STR");
	if (fp) {
		char buf[MAXBUF];
		if (fgets(buf, MAXBUF, fp)) {
			cfg.cgroup = strdup(buf);
			if (!cfg.cgroup)
				errExit("STR");
		}
		else
			goto errout;

		fclose(fp);
		return;
	}
errout:
	fwarning("STR");
	if (fp)
		fclose(fp);
}