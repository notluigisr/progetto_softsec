static void theme_show(THEME_SEARCH_REC *rec, const char *key, const char *value, int reset)
{
	MODULE_THEME_REC *theme;
	FORMAT_REC *formats;
	const char *text, *last_title;
	int n, first;

	formats = g_hash_table_lookup(default_formats, rec->name);
	theme = g_hash_table_lookup(current_theme->modules, rec->name);

	last_title = NULL; first = TRUE;
	for (n = 1; formats[n].def != NULL; n++) {
		text = theme != NULL && theme->formats[n] != NULL ?
			theme->formats[n] : formats[n].def;

		if (formats[n].tag == NULL)
			last_title = text;
		else if ((value != NULL && key != NULL && g_ascii_strcasecmp(formats[n].tag, key) == 0) ||
			 (value == NULL && (key == NULL || stristr(formats[n].tag, key) != NULL))) {
			if (first) {
				printformat(NULL, NULL, MSGLEVEL_CLIENTCRAP, TXT_FORMAT_TITLE, rec->short_name, formats[0].def);
				first = FALSE;
			}
			if (last_title != NULL)
				printformat(NULL, NULL, MSGLEVEL_CLIENTCRAP, TXT_FORMAT_SUBTITLE, last_title);
			if (reset || value != NULL) {
				theme = theme_module_create(current_theme, rec->name);
                                g_free_not_null(theme->formats[n]);
                                g_free_not_null(theme->expanded_formats[n]);

				text = reset ? formats[n].def : value;
				theme->formats[n] = reset ? NULL : g_strdup(value);
				theme->expanded_formats[n] = theme_format_expand(current_theme, text);
			}
			printformat(NULL, NULL, MSGLEVEL_CLIENTCRAP, TXT_FORMAT_ITEM, formats[n].tag, text);
			last_title = NULL;
		}
	}
}