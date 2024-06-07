load_status_changed_cb (WebKitWebView *view,
                        GParamSpec *spec,
                        EphyEmbed *embed)
{
  EphyEmbedPrivate *priv = embed->priv;
  WebKitLoadStatus status = webkit_web_view_get_load_status (view);

  if (status == WEBKIT_LOAD_COMMITTED) {
    const gchar* uri;
    EphyWebViewSecurityLevel security_level;

    uri = webkit_web_view_get_uri (view);

    ephy_embed_destroy_top_widgets (embed);

    if (g_strcmp0 (uri, priv->loading_uri) != 0) {
      g_free (priv->loading_uri);
      priv->loading_uri = g_strdup (uri);
    }

    ephy_web_view_location_changed (EPHY_WEB_VIEW (view),
                                    uri);
    restore_zoom_level (embed, uri);
    ephy_history_add_page (embed->priv->history,
                           uri,
                           FALSE,
                           FALSE);

    
    if (uri && g_str_has_prefix (uri, "STR"))
      security_level = EPHY_WEB_VIEW_STATE_IS_SECURE_HIGH;
    else
      security_level = EPHY_WEB_VIEW_STATE_IS_UNKNOWN;

    ephy_web_view_set_security_level (EPHY_WEB_VIEW (view), security_level);
  } else if (status == WEBKIT_LOAD_PROVISIONAL || status == WEBKIT_LOAD_FINISHED) {
    EphyWebViewNetState estate = EPHY_WEB_VIEW_STATE_UNKNOWN;
    char *loading_uri = NULL;

    if (status == WEBKIT_LOAD_PROVISIONAL) {
      WebKitWebFrame *frame;
      WebKitWebDataSource *source;
      WebKitNetworkRequest *request;

      frame = webkit_web_view_get_main_frame (view);
      source = webkit_web_frame_get_provisional_data_source (frame);
      request = webkit_web_data_source_get_initial_request (source);
      loading_uri = g_strdup (webkit_network_request_get_uri (request));

      
      priv->loading_uri = g_strdup (loading_uri);

      estate = (EphyWebViewNetState) (estate |
                                      EPHY_WEB_VIEW_STATE_START |
                                      EPHY_WEB_VIEW_STATE_NEGOTIATING |
                                      EPHY_WEB_VIEW_STATE_IS_REQUEST |
                                      EPHY_WEB_VIEW_STATE_IS_NETWORK);
      
      g_signal_emit_by_name (EPHY_WEB_VIEW (view), "STR", loading_uri);
    } else if (status == WEBKIT_LOAD_FINISHED) {
      loading_uri = priv->loading_uri;

      
      priv->loading_uri = NULL;

      estate = (EphyWebViewNetState) (estate |
                                      EPHY_WEB_VIEW_STATE_STOP |
                                      EPHY_WEB_VIEW_STATE_IS_DOCUMENT |
                                      EPHY_WEB_VIEW_STATE_IS_NETWORK);
    }

    ephy_web_view_update_from_net_state (EPHY_WEB_VIEW (view),
                                         loading_uri,
                                         (EphyWebViewNetState)estate);

    g_free (loading_uri);

  }
}