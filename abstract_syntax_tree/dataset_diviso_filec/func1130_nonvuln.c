static void g_test_in_ephemeral_dir(void)
{
	gchar *temp_dir = g_dir_make_tmp(NULL, NULL);
	gchar *orig_dir = g_get_current_dir();
	int err = chdir(temp_dir);
	g_assert_cmpint(err, ==, 0);

	g_test_queue_free(temp_dir);
	g_test_queue_destroy((GDestroyNotify) my_rmdir, temp_dir);
	g_test_queue_free(orig_dir);
	g_test_queue_destroy((GDestroyNotify) my_chdir, orig_dir);
}