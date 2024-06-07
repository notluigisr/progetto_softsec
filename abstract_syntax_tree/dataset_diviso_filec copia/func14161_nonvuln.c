get_iter_for_connection (GtkTreeModel *model,
					NMExportedConnection *exported,
					GtkTreeIter *iter)
{
	GtkTreeIter temp_iter;
	gboolean found = FALSE;

	if (!gtk_tree_model_get_iter_first (model, &temp_iter))
		return FALSE;

	do {
		NMExportedConnection *candidate = NULL;

		gtk_tree_model_get (model, &temp_iter, COL_CONNECTION, &candidate, -1);
		if (candidate && (candidate == exported)) {
			*iter = temp_iter;
			found = TRUE;
			break;
		}
	} while (gtk_tree_model_iter_next (model, &temp_iter));

	return found;
}