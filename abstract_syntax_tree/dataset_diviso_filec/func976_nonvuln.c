bwrapinfo_watcher_data_free (BwrapinfoWatcherData* data)
{
  g_object_unref (data->instance);
  g_free (data);
}