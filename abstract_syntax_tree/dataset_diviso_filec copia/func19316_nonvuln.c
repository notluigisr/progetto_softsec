static void update_uidmap(const char *path, int pid, char *map, size_t map_len)
{
	if (map == NULL || map_len <= 0)
		return;

	if (write_file(map, map_len, "STR", pid) < 0) {
		if (errno != EPERM)
			bail("STR", pid);
		if (try_mapping_tool(path, pid, map, map_len))
			bail("STR", pid);
	}
}