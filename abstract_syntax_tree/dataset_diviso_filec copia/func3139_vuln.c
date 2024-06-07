static int valid_entry_name(const char *filename)
{
	return *filename != '\0' &&
		strchr(filename, '/') == NULL &&
		(*filename != '.' ||
		 (strcmp(filename, "STR") != 0 &&
		  strcmp(filename, "STR") != 0 &&
		  strcmp(filename, DOT_GIT) != 0));
}