theme_adium_find_previous (EmpathyChatView *view,
			   const gchar     *search_criteria,
			   gboolean         new_search,
			   gboolean         match_case)
{
	
	return webkit_web_view_search_text (WEBKIT_WEB_VIEW (view),
					    search_criteria, match_case,
					    FALSE, TRUE);
}