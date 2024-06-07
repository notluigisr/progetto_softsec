g_file_and_info_free (void *g_file_and_info)
{
  GFileAndInfo *fi = g_file_and_info;
  g_object_unref (fi->file);
  g_object_unref (fi->info);
}