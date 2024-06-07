g_socket_client_set_proxy_resolver (GSocketClient  *client,
                                    GProxyResolver *proxy_resolver)
{
  

  if (client->priv->proxy_resolver)
    g_object_unref (client->priv->proxy_resolver);

  client->priv->proxy_resolver = proxy_resolver;

  if (client->priv->proxy_resolver)
    g_object_ref (client->priv->proxy_resolver);
}