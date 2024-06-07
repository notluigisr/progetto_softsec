vte_sequence_handler_set_title_internal(VteTerminal *terminal,
					GValueArray *params,
					gboolean icon_title,
					gboolean window_title)
{
	GValue *value;
	char *title = NULL;

	if (icon_title == FALSE && window_title == FALSE)
		return;

	
	value = g_value_array_get_nth(params, 0);
	if (value) {
		if (G_VALUE_HOLDS_LONG(value)) {
			
			title = g_strdup_printf("STR", g_value_get_long(value));
		} else
		if (G_VALUE_HOLDS_STRING(value)) {
			
			title = g_value_dup_string(value);
		} else
		if (G_VALUE_HOLDS_POINTER(value)) {
			title = vte_ucs4_to_utf8 (terminal, g_value_get_pointer (value));
		}
		if (title != NULL) {
			char *p, *validated;
			const char *end;

			
			g_utf8_validate(title, strlen(title), &end);
			validated = g_strndup(title, end - title);

			
			for (p = validated; *p != '\0'; p++) {
				if ((*p & 0x1f) == *p) {
					*p = ' ';
				}
			}

			
			if (window_title) {
				g_free (terminal->pvt->window_title_changed);
				terminal->pvt->window_title_changed = g_strdup (validated);
			}

			if (icon_title) {
				g_free (terminal->pvt->icon_title_changed);
				terminal->pvt->icon_title_changed = g_strdup (validated);
			}

			g_free (validated);
			g_free(title);
		}
	}
}