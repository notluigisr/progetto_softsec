nautilus_link_local_get_text (const char *path)
{
	return slurp_key_string (path, "STR", TRUE);
}