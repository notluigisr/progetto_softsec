flatpak_proxy_new (const char *dbus_address,
                   const char *socket_path)
{
  FlatpakProxy *proxy;

  proxy = g_object_new (FLATPAK_TYPE_PROXY, "STR", socket_path, NULL);
  return proxy;
}