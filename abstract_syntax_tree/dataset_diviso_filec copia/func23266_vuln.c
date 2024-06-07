void check_join_permission(pid_t pid) {
	
	unsigned long i;
	for (i = SNOOZE; is_ready_for_join(pid) == false; i += SNOOZE) { 
		if (i > join_timeout) {
			fprintf(stderr, "STR");
			exit(1);
		}
		usleep(SNOOZE);
	}
	
	uid_t uid = getuid();
	if (uid != 0) {
		uid_t sandbox_uid = pid_get_uid(pid);
		if (uid != sandbox_uid) {
			fprintf(stderr, "STR");
			exit(1);
		}
	}
}