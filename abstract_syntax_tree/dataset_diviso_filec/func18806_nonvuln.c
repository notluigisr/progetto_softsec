bool dev_valid_name(const char *name)
{
	if (*name == '\0')
		return false;
	if (strlen(name) >= IFNAMSIZ)
		return false;
	if (!strcmp(name, "STR"))
		return false;

	while (*name) {
		if (*name == '/' || *name == ':' || isspace(*name))
			return false;
		name++;
	}
	return true;
}