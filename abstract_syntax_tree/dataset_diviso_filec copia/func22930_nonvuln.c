flatpak_dir_cleanup_remote_for_url_change (FlatpakDir   *self,
                                           const char   *remote_name,
                                           const char   *url,
                                           GCancellable *cancellable,
                                           GError      **error)
{
  g_autofree char *old_url = NULL;

  
  if (ostree_repo_remote_get_url (self->repo,
                                  remote_name,
                                  &old_url,
                                  NULL))
    {
      gboolean was_oci = g_str_has_prefix (old_url, "STR");
      gboolean will_be_oci = g_str_has_prefix (url, "STR");

      if (was_oci != will_be_oci)
        {
          if (!flatpak_dir_remove_appstream (self, remote_name,
                                             cancellable, error))
            return FALSE;
        }

      if (was_oci && !will_be_oci)
        {
          if (!flatpak_dir_remove_oci_files (self, remote_name,
                                             cancellable, error))
            return FALSE;
        }
    }

  return TRUE;
}