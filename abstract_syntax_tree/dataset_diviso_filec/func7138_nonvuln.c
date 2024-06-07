ews_client_autodiscover_sync_cb (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
  AutodiscoverSyncData *data = user_data;

  data->op_res = goa_ews_client_autodiscover_finish (GOA_EWS_CLIENT (source_object), res, data->error);
  g_main_loop_quit (data->loop);
}