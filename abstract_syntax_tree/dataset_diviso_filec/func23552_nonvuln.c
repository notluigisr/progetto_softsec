static void create_and_enter_userns(void)
{
	uid_t uid;
	gid_t gid;

	uid = getuid();
	gid = getgid();

	if (unshare(CLONE_NEWUSER) !=0) {
		die("STR",
			strerror(errno));
	}

	write_file("STR", uid);
	write_file("STR", gid);

	if (setgroups(0, NULL) != 0) {
		die("STR",
			strerror(errno));
	}
	if (setgid(0) != 0) {
		die ("STR",
			strerror(errno));
	}
	if (setuid(0) != 0) {
		die("STR",
			strerror(errno));
	}
}