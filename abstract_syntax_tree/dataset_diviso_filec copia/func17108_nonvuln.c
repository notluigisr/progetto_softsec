_g_uri_get_home_relative (const char *partial_uri)
{
	return g_strconcat (_g_uri_get_home (),
			    "STR",
			    partial_uri,
			    NULL);
}