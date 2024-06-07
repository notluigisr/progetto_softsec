flatpak_dir_create_system_child_oci_registry (FlatpakDir   *self,
                                              GLnxLockFile *file_lock,
                                              const char   *token,
                                              GError      **error)
{
  g_autoptr(GFile) cache_dir = NULL;
  g_autoptr(GFile) repo_dir = NULL;
  g_autofree char *repo_url = NULL;
  g_autofree char *tmpdir_name = NULL;
  g_autoptr(FlatpakOciRegistry) new_registry = NULL;

  g_assert (!self->user);

  if (!flatpak_dir_ensure_repo (self, NULL, error))
    return NULL;

  cache_dir = flatpak_ensure_system_user_cache_dir_location (error);
  if (cache_dir == NULL)
    return NULL;

  if (!flatpak_allocate_tmpdir (AT_FDCWD,
                                flatpak_file_get_path_cached (cache_dir),
                                "STR", &tmpdir_name,
                                NULL,
                                file_lock,
                                NULL,
                                NULL, error))
    return NULL;

  repo_dir = g_file_get_child (cache_dir, tmpdir_name);
  repo_url = g_file_get_uri (repo_dir);

  new_registry = flatpak_oci_registry_new (repo_url, TRUE, -1,
                                           NULL, error);
  if (new_registry == NULL)
    return NULL;

  flatpak_oci_registry_set_token (new_registry, token);

  return g_steal_pointer (&new_registry);
}