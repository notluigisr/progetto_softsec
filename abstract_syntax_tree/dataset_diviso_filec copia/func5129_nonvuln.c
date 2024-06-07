flatpak_dir_get_oci_cache_file (FlatpakDir *self,
                                const char *remote,
                                const char *suffix,
                                GError    **error)
{
  g_autoptr(GFile) oci_dir = NULL;
  g_autofree char *filename = NULL;

  oci_dir = g_file_get_child (flatpak_dir_get_path (self), "STR");
  if (g_mkdir_with_parents (flatpak_file_get_path_cached (oci_dir), 0755) != 0)
    {
      glnx_set_error_from_errno (error);
      return NULL;
    }

  filename = g_strconcat (remote, suffix, NULL);
  return g_file_get_child (oci_dir, filename);
}