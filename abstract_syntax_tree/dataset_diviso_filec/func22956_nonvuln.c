flatpak_dir_recreate_repo (FlatpakDir   *self,
                           GCancellable *cancellable,
                           GError      **error)
{
  gboolean res;
  OstreeRepo *old_repo = g_steal_pointer (&self->repo);

  
  g_clear_object (&self->cache_dir);

  res = flatpak_dir_ensure_repo (self, cancellable, error);
  g_clear_object (&old_repo);

  G_LOCK (config_cache);

  g_clear_pointer (&self->masked, g_regex_unref);
  g_clear_pointer (&self->pinned, g_regex_unref);

  G_UNLOCK (config_cache);

  return res;
}