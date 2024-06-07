static int read_record(int rhport, char *host, unsigned long host_len,
		char *port, unsigned long port_len, char *busid)
{
	int part;
	FILE *file;
	char path[PATH_MAX+1];
	char *buffer, *start, *end;
	char delim[] = {' ', ' ', '\n'};
	int max_len[] = {(int)host_len, (int)port_len, SYSFS_BUS_ID_SIZE};
	size_t buffer_len = host_len + port_len + SYSFS_BUS_ID_SIZE + 4;

	buffer = malloc(buffer_len);
	if (!buffer)
		return -1;

	snprintf(path, PATH_MAX, VHCI_STATE_PATH"STR", rhport);

	file = fopen(path, "STR");
	if (!file) {
		err("STR");
		free(buffer);
		return -1;
	}

	if (fgets(buffer, buffer_len, file) == NULL) {
		err("STR");
		free(buffer);
		fclose(file);
		return -1;
	}
	fclose(file);

	
	start = buffer;
	for (part = 0; part < 3; part++) {
		end = strchr(start, delim[part]);
		if (end == NULL || (end - start) > max_len[part]) {
			free(buffer);
			return -1;
		}
		start = end + 1;
	}

	if (sscanf(buffer, "STR", host, port, busid) != 3) {
		err("STR");
		free(buffer);
		return -1;
	}

	free(buffer);

	return 0;
}