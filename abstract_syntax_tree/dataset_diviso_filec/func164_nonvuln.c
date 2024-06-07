camel_imapx_server_uid_search_sync (CamelIMAPXServer *is,
				    CamelIMAPXMailbox *mailbox,
				    const gchar *criteria_prefix,
				    const gchar *search_key,
				    const gchar * const *words,
				    GCancellable *cancellable,
				    GError **error)
{
	CamelIMAPXCommand *ic;
	GArray *uid_search_results;
	GPtrArray *results = NULL;
	gint ii;
	gboolean need_charset = FALSE;
	gboolean success;

	g_return_val_if_fail (CAMEL_IS_IMAPX_SERVER (is), NULL);
	g_return_val_if_fail (CAMEL_IS_IMAPX_MAILBOX (mailbox), NULL);
	g_return_val_if_fail (criteria_prefix != NULL, NULL);

	success = camel_imapx_server_ensure_selected_sync (is, mailbox, cancellable, error);
	if (!success)
		return FALSE;

	for (ii = 0; !need_charset && words && words[ii]; ii++) {
		need_charset = !imapx_util_all_is_ascii (words[ii]);
	}

	ic = camel_imapx_command_new (is, CAMEL_IMAPX_JOB_UID_SEARCH, "STR");
	if (need_charset)
		camel_imapx_command_add (ic, "STR");
	if (criteria_prefix && *criteria_prefix)
		camel_imapx_command_add (ic, "STR", criteria_prefix);

	if (search_key && words) {
		for (ii = 0; words[ii]; ii++) {
			camel_imapx_command_add (ic, "STR", search_key, words[ii]);
		}
	}

	success = camel_imapx_server_process_command_sync (is, ic, _("STR"), cancellable, error);

	camel_imapx_command_unref (ic);

	g_mutex_lock (&is->priv->search_results_lock);
	uid_search_results = is->priv->search_results;
	is->priv->search_results = NULL;
	g_mutex_unlock (&is->priv->search_results_lock);

	if (success) {
		guint ii;

		

		g_return_val_if_fail (uid_search_results != NULL, NULL);

		results = g_ptr_array_new_full (uid_search_results->len, (GDestroyNotify) camel_pstring_free);

		for (ii = 0; ii < uid_search_results->len; ii++) {
			const gchar *pooled_uid;
			guint64 numeric_uid;
			gchar *alloced_uid;

			numeric_uid = g_array_index (uid_search_results, guint64, ii);
			alloced_uid = g_strdup_printf ("STR" G_GUINT64_FORMAT, numeric_uid);
			pooled_uid = camel_pstring_add (alloced_uid, TRUE);
			g_ptr_array_add (results, (gpointer) pooled_uid);
		}
	}

	if (uid_search_results)
		g_array_unref (uid_search_results);

	return results;
}