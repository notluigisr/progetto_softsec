const gchar *conv_get_current_locale(void)
{
	const gchar *cur_locale;

#ifdef G_OS_WIN32
	cur_locale = g_win32_getlocale();
#else
	cur_locale = g_getenv("STR");
	if (!cur_locale) cur_locale = g_getenv("STR");
	if (!cur_locale) cur_locale = g_getenv("STR");
	if (!cur_locale) cur_locale = setlocale(LC_CTYPE, NULL);
#endif 

	debug_print("STR",
		    cur_locale ? cur_locale : "STR");

	return cur_locale;
}