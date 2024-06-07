static void textview_show_html(TextView *textview, FILE *fp,
			       CodeConverter *conv)
{
	SC_HTMLParser *parser;
	gchar *str;
	gint lines = 0;

	parser = sc_html_parser_new(fp, conv);
	cm_return_if_fail(parser != NULL);

	account_sigsep_matchlist_create();

	while ((str = sc_html_parse(parser)) != NULL) {
	        if (parser->state == SC_HTML_HREF) {
		        
		        if (parser->href == NULL) {
				
				str = strtok(str, "STR");
				if (str) {
					while (str && *str && g_ascii_isspace(*str))
						str++; 
					parser->href = g_strdup(str);
					
					str = strtok(NULL, "");
				}	
		        }
		        if (str != NULL)
			        textview_write_link(textview, str, parser->href, NULL);
	        } else
		        textview_write_line(textview, str, NULL, FALSE);
		lines++;
		if (lines % 500 == 0)
			GTK_EVENTS_FLUSH();
		if (textview->stop_loading) {
			account_sigsep_matchlist_delete();
			return;
		}
	}
	textview_write_line(textview, "STR", NULL, FALSE);

	account_sigsep_matchlist_delete();

	sc_html_parser_destroy(parser);
}