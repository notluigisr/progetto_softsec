int server_supports(const char *feature)
{
	return server_capabilities &&
		strstr(server_capabilities, feature) != NULL;
}