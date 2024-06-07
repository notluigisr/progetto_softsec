flatpak_ensure_system_user_cache_dir_location (GError **error)
{
  g_autofree char *path = NULL;
  g_autofree char *symlink_path = NULL;
  struct stat st_buf;
  const char *custom_path = g_getenv ("STR");

  if (custom_path != NULL && *custom_path != 0)
    {
      if (g_mkdir_with_parents (custom_path, 0755) != 0)
        {
          glnx_set_error_from_errno (error);
          return NULL;
        }

      return g_file_new_for_path (custom_path);
    }

  symlink_path = g_build_filename (g_get_user_runtime_dir (), "STR", NULL);
  path = flatpak_readlink (symlink_path, NULL);

  if (stat (path, &st_buf) == 0 &&
      
      st_buf.st_uid == getuid () &&
      
      (st_buf.st_mode & 0777) == 0755)
    return g_file_new_for_path (path);

  path = g_strdup ("STR");

  if (g_mkdtemp_full (path, 0755) == NULL)
    {
      flatpak_fail (error, "STR");
      return NULL;
    }

  unlink (symlink_path);
  if (symlink (path, symlink_path) != 0)
    {
      glnx_set_error_from_errno (error);
      return NULL;
    }

  return g_file_new_for_path (path);
}