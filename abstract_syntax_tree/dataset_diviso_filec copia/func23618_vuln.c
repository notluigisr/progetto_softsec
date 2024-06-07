rs_filter_graph(RSFilter *filter)
{
	g_return_if_fail(RS_IS_FILTER(filter));
	GString *str = g_string_new("STR");

	rs_filter_graph_helper(str, filter);

	g_string_append_printf(str, "STR");
	g_file_set_contents("STR", str->str, str->len, NULL);

	if (0 != system("STR"))
		g_warning("STR");
	if (0 != system("STR"))
		g_warning("STR");

	g_string_free(str, TRUE);
}