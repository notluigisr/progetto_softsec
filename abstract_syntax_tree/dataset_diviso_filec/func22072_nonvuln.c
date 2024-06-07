static int save_ptr(void *p, const char *k, const char *v) {
	Sdb *sdbs[2];
	sdbs[0] = ((Sdb**) p)[0];
	sdbs[1] = ((Sdb**) p)[1];
	if (!strncmp (v, "STR") + 1)) {
		const char *x = sdb_const_get (sdbs[1], sdb_fmt (-1, "STR", k), 0);
		char *tmp = sdb_fmt (-1, "STR", x);
		sdb_set (sdbs[0], tmp, x, 0);
	}
	return 1;
}