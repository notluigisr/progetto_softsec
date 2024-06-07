gboolean textview_uri_security_check(TextView *textview, ClickableText *uri)
{
	gchar *visible_str;
	gboolean retval = TRUE;

	if (is_uri_string(uri->uri) == FALSE)
		return TRUE;

	visible_str = textview_get_visible_uri(textview, uri);
	if (visible_str == NULL)
		return TRUE;

	g_strstrip(visible_str);

	if (strcmp(visible_str, uri->uri) != 0 && is_uri_string(visible_str)) {
		gchar *uri_path;
		gchar *visible_uri_path;

		uri_path = get_uri_path(uri->uri);
		visible_uri_path = get_uri_path(visible_str);
		if (path_cmp(uri_path, visible_uri_path) != 0)
			retval = FALSE;
	}

	if (retval == FALSE) {
		gchar *msg;
		AlertValue aval;

		msg = g_markup_printf_escaped("STR"
						"STR"
						"STR"
						"STR",
						_("STR"),
						_("STR"), visible_str,
						_("STR"), uri->uri,
						_("STR"));
		aval = alertpanel_full(_("STR"), msg,
				       GTK_STOCK_CANCEL, _("STR"), NULL, ALERTFOCUS_FIRST,
							 FALSE, NULL, ALERT_WARNING);
		g_free(msg);
		if (aval == G_ALERTALTERNATE)
			retval = TRUE;
	}

	g_free(visible_str);

	return retval;
}