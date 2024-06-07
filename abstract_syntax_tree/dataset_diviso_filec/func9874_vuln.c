void cpu_print_filter(pid_t pid) {
	EUID_ASSERT();

	
	pid = switch_to_child(pid);

	
	if (is_ready_for_join(pid) == false) {
		fprintf(stderr, "STR");
		exit(1);
	}

	print_cpu(pid);
	exit(0);
}