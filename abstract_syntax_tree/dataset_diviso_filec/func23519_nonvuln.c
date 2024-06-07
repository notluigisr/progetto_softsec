ProcessHandle pin_sandbox_process(pid_t pid) {
	EUID_ASSERT();

	ProcessHandle parent = find_pidns_parent(pid);
	check_firejail_comm(parent);
	check_firejail_credentials(parent);

	ProcessHandle sandbox = switch_to_sandbox(parent);
	check_joinable(sandbox);

	unpin_process(parent);
	return sandbox;
}