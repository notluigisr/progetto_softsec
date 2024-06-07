flatpak_dir_remove_appstream (FlatpakDir   *self,
                              const char   *remote,
                              GCancellable *cancellable,
                              GError      **error)
{
  g_autoptr(GFile) appstream_dir = NULL;
  g_autoptr(GFile) remote_dir = NULL;

  if (!flatpak_dir_ensure_repo (self, cancellable, error))
    return FALSE;

  appstream_dir = g_file_get_child (flatpak_dir_get_path (self), "STR");
  remote_dir = g_file_get_child (appstream_dir, remote);

  if (g_file_query_exists (remote_dir, cancellable) &&
      !flatpak_rm_rf (remote_dir, cancellable, error))
    return FALSE;

  return TRUE;
}