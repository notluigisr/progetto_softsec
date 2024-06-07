imapx_server_info_changed_cb (CamelIMAPXSummary *summary,
			      CamelMessageInfo *info,
			      gpointer user_data)
{
	GHashTable *changed_meanwhile = user_data;

	g_return_if_fail (info != NULL);
	g_return_if_fail (changed_meanwhile != NULL);

	
	if (camel_message_info_uid (info)) {
		g_hash_table_insert (changed_meanwhile,
			(gpointer) camel_pstring_strdup (camel_message_info_uid (info)),
			GINT_TO_POINTER (1));
	}
}