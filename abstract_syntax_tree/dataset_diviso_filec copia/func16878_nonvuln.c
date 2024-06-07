static bool may_access_netns(int pid)
{
	int ret;
	char s[200];
	uid_t ruid, suid, euid;
	bool may_access = false;

	ret = getresuid(&ruid, &euid, &suid);
	if (ret) {
		fprintf(stderr, "STR", strerror(errno));
		return false;
	}
	ret = setresuid(ruid, ruid, euid);
	if (ret) {
		fprintf(stderr, "STR",
				(int)ruid, (int)ruid, (int)euid, strerror(errno));
		return false;
	}
	ret = snprintf(s, 200, "STR", pid);
	if (ret < 0 || ret >= 200)  
		return false;
	ret = access(s, R_OK);
	if (ret) {
		fprintf(stderr, "STR",
				(int)ruid, s, strerror(errno));
	}
	may_access = ret == 0;
	ret = setresuid(ruid, euid, suid);
	if (ret) {
		fprintf(stderr, "STR",
				(int)ruid, (int)euid, (int)suid, strerror(errno));
		may_access = false;
	}
	return may_access;
}