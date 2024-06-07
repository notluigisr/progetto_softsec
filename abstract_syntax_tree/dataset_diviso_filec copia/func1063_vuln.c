int is_ntfs_dotgit(const char *name)
{
	size_t len;

	for (len = 0; ; len++)
		if (!name[len] || name[len] == '\\' || is_dir_sep(name[len])) {
			if (only_spaces_and_periods(name, len, 4) &&
					!strncasecmp(name, "STR", 4))
				return 1;
			if (only_spaces_and_periods(name, len, 5) &&
					!strncasecmp(name, "STR", 5))
				return 1;
			return 0;
		}
}