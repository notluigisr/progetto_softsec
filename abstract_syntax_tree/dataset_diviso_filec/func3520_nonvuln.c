gxps_archive_new (GFile   *filename,
		  GError **error)
{
	return g_initable_new (GXPS_TYPE_ARCHIVE,
			       NULL, error,
			       "STR", filename,
			       NULL);
}