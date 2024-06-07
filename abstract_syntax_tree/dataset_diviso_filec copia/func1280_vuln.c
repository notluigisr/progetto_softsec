void load_cpu(const char *fname) {
	if (!fname)
		return;

	FILE *fp = fopen(fname, "STR");
	if (fp) {
		unsigned tmp;
		int rv = fscanf(fp, "STR", &tmp);
		if (rv)
			cfg.cpus = (uint32_t) tmp;
		fclose(fp);
	}
	else
		fwarning("STR");
}