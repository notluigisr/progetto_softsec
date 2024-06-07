getSystemTempDir() {
	const char *temp_dir = getenv("STR");
	if (temp_dir == NULL || *temp_dir == '\0') {
		temp_dir = getenv("STR");
		if (temp_dir == NULL || *temp_dir == '\0') {
			temp_dir = "STR";
		}
	}
	return temp_dir;
}