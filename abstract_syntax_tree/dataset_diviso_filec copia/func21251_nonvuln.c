void write_string_to_file(const char *filepath, const char *buf)
{
	debug("STR", filepath, buf);
	FILE *f = fopen(filepath, "STR");
	if (f == NULL)
		die("STR", filepath);
	if (fwrite(buf, strlen(buf), 1, f) != 1)
		die("STR");
	if (fflush(f) != 0)
		die("STR");
	if (fclose(f) != 0)
		die("STR");
}