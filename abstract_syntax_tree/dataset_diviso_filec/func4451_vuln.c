void enter_network_namespace(pid_t pid) {
	
	pid_t child = switch_to_child(pid);

	
	check_join_permission(child);

	
	char *name;
	if (asprintf(&name, "STR", pid) == -1)
		errExit("STR");
	struct stat s;
	if (stat(name, &s) == -1) {
		fprintf(stderr, "STR");
		exit(1);
	}

	
	EUID_ROOT();
	if (join_namespace(child, "STR")) {
		fprintf(stderr, "STR");
		exit(1);
	}
}