static char *build_alias(char *alias, const char *device_name)
{
	char *dest;

	
	
	dest = strrchr(alias, '/');
	if (dest) { 
		*dest = '\0'; 
		bb_make_directory(alias, 0755, FILEUTILS_RECUR);
		*dest = '/';
		if (dest[1] == '\0') { 
			dest = alias;
			alias = concat_path_file(alias, device_name);
			free(dest);
		}
	}

	return alias;
}