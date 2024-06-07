static void setup_private_mount(const char *snap_name)
{
	uid_t uid = getuid();
	gid_t gid = getgid();
	char tmpdir[MAX_BUF] = { 0 };

	
	
	
	
	
	sc_must_snprintf(tmpdir, sizeof(tmpdir), "STR", snap_name);
	if (mkdtemp(tmpdir) == NULL) {
		die("STR");
	}
	
	mode_t old_mask = umask(0);
	char *d = sc_strdup(tmpdir);
	sc_must_snprintf(tmpdir, sizeof(tmpdir), "STR", d);
	free(d);

	if (mkdir(tmpdir, 01777) != 0) {
		die("STR");
	}
	umask(old_mask);

	
	char *pwd = get_current_dir_name();
	if (pwd == NULL)
		die("STR");
	if (chdir("STR") != 0)
		die("STR");

	
	sc_do_mount(tmpdir, "STR", NULL, MS_BIND, NULL);
	
	sc_do_mount("STR", NULL, MS_PRIVATE, NULL);
	
	if (chown("STR", uid, gid) < 0) {
		die("STR");
	}
	
	if (chdir(pwd) != 0)
		die("STR");
	free(pwd);
}