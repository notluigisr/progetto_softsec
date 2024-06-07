e_ews_connection_get_folder_permissions_sync (EEwsConnection *cnc,
                                              gint pri,
                                              EwsFolderId *folder_id,
                                              GSList **permissions,
                                              GCancellable *cancellable,
                                              GError **error)
{
	EAsyncClosure *closure;
	GAsyncResult *result;
	gboolean success;

	g_return_val_if_fail (E_IS_EWS_CONNECTION (cnc), FALSE);
	g_return_val_if_fail (folder_id != NULL, FALSE);
	g_return_val_if_fail (permissions != NULL, FALSE);

	closure = e_async_closure_new ();

	e_ews_connection_get_folder_permissions (
		cnc, pri, folder_id, cancellable,
		e_async_closure_callback, closure);

	result = e_async_closure_wait (closure);

	success = e_ews_connection_get_folder_permissions_finish (
		cnc, result, permissions, error);

	e_async_closure_free (closure);

	return success;
}