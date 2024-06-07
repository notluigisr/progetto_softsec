static void window_themes_update(void)
{
	GSList *tmp;

	for (tmp = windows; tmp != NULL; tmp = tmp->next) {
		WINDOW_REC *rec = tmp->data;

		if (rec->theme_name != NULL)
                        rec->theme = theme_load(rec->theme_name);
	}
}