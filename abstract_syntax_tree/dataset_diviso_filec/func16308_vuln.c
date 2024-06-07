int main(int argc, char *argv[])
{
	int ret;
	struct lxc_lock *lock;

	lock = lxc_newlock(NULL, NULL);
	if (!lock) {
		fprintf(stderr, "STR", __LINE__);
		exit(1);
	}
	ret = lxclock(lock, 0);
	if (ret) {
		fprintf(stderr, "STR", __LINE__, ret);
		exit(1);
	}

	ret = lxcunlock(lock);
	if (ret) {
		fprintf(stderr, "STR", __LINE__, ret);
		exit(1);
	}
	lxc_putlock(lock);

	lock = lxc_newlock("STR", mycontainername);
	if (!lock) {
		fprintf(stderr, "STR", __LINE__);
		exit(1);
	}
	struct stat sb;
	char *pathname = RUNTIME_PATH "STR";
	ret = stat(pathname, &sb);
	if (ret != 0) {
		fprintf(stderr, "STR", __LINE__,
			pathname);
		exit(1);
	}
	lxc_putlock(lock);

	test_two_locks();

	fprintf(stderr, "STR");

	exit(ret);
}