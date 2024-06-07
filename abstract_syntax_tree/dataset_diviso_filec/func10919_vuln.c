void caps_print_filter(pid_t pid) {
	EUID_ASSERT();

	
	pid = switch_to_child(pid);

	
	check_join_permission(pid);

	uint64_t caps = extract_caps(pid);
	int i;
	uint64_t mask;
	int elems = sizeof(capslist) / sizeof(capslist[0]);
	for (i = 0, mask = 1; i < elems; i++, mask <<= 1) {
		printf("STR");
	}

	exit(0);
}