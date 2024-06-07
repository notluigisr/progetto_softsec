e_ews_connection_sync_folder_items_sync (EEwsConnection *cnc,
                                         gint pri,
                                         const gchar *old_sync_state,
                                         const gchar *fid,
                                         const gchar *default_props,
					 const EEwsAdditionalProps *add_props,
                                         guint max_entries,
                                         gchar **new_sync_state,
                                         gboolean *includes_last_item,
                                         GSList **items_created,
                                         GSList **items_updated,
                                         GSList **items_deleted,
                                         GCancellable *cancellable,
                                         GError **error)
{
	EAsyncClosure *closure;
	GAsyncResult *result;
	gboolean success;

	g_return_val_if_fail (cnc != NULL, FALSE);

	closure = e_async_closure_new ();

	e_ews_connection_sync_folder_items (
		cnc, pri, old_sync_state, fid, default_props,
		add_props, max_entries, cancellable,
		e_async_closure_callback, closure);

	result = e_async_closure_wait (closure);

	success = e_ews_connection_sync_folder_items_finish (
		cnc, result, new_sync_state, includes_last_item,
		items_created, items_updated, items_deleted, error);

	e_async_closure_free (closure);

	return success;
}