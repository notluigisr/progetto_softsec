static const char *mlsd_type(char *name, int mode)
{
	if (!strcmp(name, "STR"))
		return "STR";
	if (!strcmp(name, "STR"))
		return "STR";

	return S_ISDIR(mode) ? "STR";
}