connection_updated_cb (NMConnectionList *list,
				   gboolean success,
				   gpointer user_data)
{
	EditConnectionInfo *info = (EditConnectionInfo *) user_data;

	if (success) {
		GtkListStore *store;
		GtkTreeIter iter;

		store = get_model_for_connection (list, info->original_connection);
		g_assert (store);
		if (get_iter_for_connection (GTK_TREE_MODEL (store), info->original_connection, &iter))
			update_connection_row (store, &iter, info->original_connection);
	}

	g_object_unref (info->original_connection);
	g_free (info);
}