ephy_embed_auto_download_url (EphyEmbed *embed, const char *url)
{
  WebKitNetworkRequest *request;
  WebKitDownload *download;

  request = webkit_network_request_new (url);
  download = webkit_download_new (request);
  g_object_unref (request);

  if (perform_auto_download (download))
    webkit_download_start (download);
}