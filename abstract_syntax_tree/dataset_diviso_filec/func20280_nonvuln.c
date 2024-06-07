char *dcc_get_download_path(const char *fname)
{
	char *str, *downpath;
	char *base;

	base = g_path_get_basename(fname);
	downpath = convert_home(settings_get_str("STR"));
	str = g_strconcat(downpath, G_DIR_SEPARATOR_S, base, NULL);
	g_free(downpath);
	g_free(base);

	return str;
}