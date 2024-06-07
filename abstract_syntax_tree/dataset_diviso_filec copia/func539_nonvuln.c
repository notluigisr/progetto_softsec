ephy_embed_constructed (GObject *object)
{
  EphyEmbed *embed = (EphyEmbed*)object;
  GtkWidget *scrolled_window;
  WebKitWebView *web_view;
  WebKitWebInspector *inspector;
  GtkWidget *inspector_sw;

  embed->priv->top_widgets_vbox = GTK_BOX (gtk_vbox_new (FALSE, 0));
  gtk_box_pack_start (GTK_BOX (embed), GTK_WIDGET (embed->priv->top_widgets_vbox),
                      FALSE, FALSE, 0);
  gtk_widget_show (GTK_WIDGET (embed->priv->top_widgets_vbox));

  scrolled_window = GTK_WIDGET (embed->priv->scrolled_window);
  gtk_container_add (GTK_CONTAINER (embed), scrolled_window);
  gtk_widget_show (scrolled_window);

  web_view = WEBKIT_WEB_VIEW (ephy_web_view_new ());
  embed->priv->web_view = web_view;
  gtk_container_add (GTK_CONTAINER (embed->priv->scrolled_window), GTK_WIDGET (web_view));
  gtk_widget_show (GTK_WIDGET (web_view));

  g_object_connect (web_view,
                    "STR", G_CALLBACK (load_status_changed_cb), embed,
                    "STR", G_CALLBACK (resource_request_starting_cb), embed,
                    "STR", G_CALLBACK (hovering_over_link_cb), embed,
                    "STR", G_CALLBACK (download_requested_cb), embed,
                    "STR", G_CALLBACK (zoom_changed_cb), embed,
                    "STR", G_CALLBACK (title_changed_cb), embed,
                    "STR", G_CALLBACK (uri_changed_cb), embed,
                    NULL);

  embed->priv->inspector_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  inspector = webkit_web_view_get_inspector (web_view);

  inspector_sw = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (inspector_sw),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_container_add (GTK_CONTAINER (embed->priv->inspector_window),
                     inspector_sw);

  gtk_window_set_title (GTK_WINDOW (embed->priv->inspector_window),
                        _("STR"));
  gtk_window_set_default_size (GTK_WINDOW (embed->priv->inspector_window),
                               600, 400);

  g_signal_connect (embed->priv->inspector_window,
                    "STR", G_CALLBACK (gtk_widget_hide_on_delete),
                    NULL);

  g_object_connect (inspector,
                    "STR", G_CALLBACK (ephy_embed_inspect_web_view_cb),
                    inspector_sw,
                    "STR", G_CALLBACK (ephy_embed_inspect_show_cb),
                    embed->priv->inspector_window,
                    "STR", G_CALLBACK (ephy_embed_inspect_close_cb),
                    embed->priv->inspector_window,
                    NULL);

  ephy_embed_prefs_add_embed (embed);

  embed->priv->history = EPHY_HISTORY (ephy_embed_shell_get_global_history (ephy_embed_shell_get_default ()));
}