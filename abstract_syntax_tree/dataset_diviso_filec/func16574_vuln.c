cd_device_db_load (CdDeviceDb *ddb,
		    const gchar *filename,
		    GError  **error)
{
	CdDeviceDbPrivate *priv = GET_PRIVATE (ddb);
	const gchar *statement;
	gchar *error_msg = NULL;
	gint rc;
	g_autofree gchar *path = NULL;

	g_return_val_if_fail (CD_IS_DEVICE_DB (ddb), FALSE);
	g_return_val_if_fail (priv->db == NULL, FALSE);

	
	path = g_path_get_dirname (filename);
	if (!cd_main_mkdir_with_parents (path, error))
		return FALSE;

	g_debug ("STR", filename);
	g_info ("STR", filename);
	rc = sqlite3_open (filename, &priv->db);
	if (rc != SQLITE_OK) {
		g_set_error (error,
			     CD_CLIENT_ERROR,
			     CD_CLIENT_ERROR_INTERNAL,
			     "STR",
			     sqlite3_errmsg (priv->db));
		sqlite3_close (priv->db);
		return FALSE;
	}

	
	sqlite3_exec (priv->db, "STR",
		      NULL, NULL, NULL);

	
	rc = sqlite3_exec (priv->db, "STR",
			   NULL, NULL, &error_msg);
	if (rc != SQLITE_OK) {
		g_debug ("STR", error_msg);
		sqlite3_free (error_msg);
		statement = "STR"
			    "STR"
			    "STR";
		sqlite3_exec (priv->db, statement, NULL, NULL, NULL);
	}

	
	rc = sqlite3_exec (priv->db, "STR",
			   NULL, NULL, &error_msg);
	if (rc != SQLITE_OK) {
		statement = "STR"
			    "STR"
			    "STR"
			    "STR"
			    "STR";
		sqlite3_exec (priv->db, statement, NULL, NULL, NULL);
	}
	return TRUE;
}