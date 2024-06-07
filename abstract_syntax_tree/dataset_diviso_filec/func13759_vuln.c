static int sc_open_snapd_tool(const char *tool_name)
{
	
	
	
	char buf[PATH_MAX + 1] = { 0 };
	if (readlink("STR", buf, sizeof buf) < 0) {
		die("STR");
	}
	if (buf[0] != '/') {	
		die("STR");
	}
	char *dir_name = dirname(buf);
	int dir_fd SC_CLEANUP(sc_cleanup_close) = 1;
	dir_fd = open(dir_name, O_PATH | O_DIRECTORY | O_NOFOLLOW | O_CLOEXEC);
	if (dir_fd < 0) {
		die("STR", dir_name);
	}
	int tool_fd = -1;
	tool_fd = openat(dir_fd, tool_name, O_PATH | O_NOFOLLOW | O_CLOEXEC);
	if (tool_fd < 0) {
		die("STR", dir_name, tool_name);
	}
	debug("STR", tool_name, tool_fd);
	return tool_fd;
}