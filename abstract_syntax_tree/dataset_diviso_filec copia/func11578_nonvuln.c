e_ews_calendar_to_free (EEwsCalendarTo *to) {
	if (to != NULL) {
		g_free (to->kind);
		g_free (to->value);
	}
}