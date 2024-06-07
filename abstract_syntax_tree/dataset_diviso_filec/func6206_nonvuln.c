flatpak_dir_get_remote_filter (FlatpakDir *self,
                               const char *remote_name)
{
  GKeyFile *config = flatpak_dir_get_repo_config (self);
  g_autofree char *group = get_group (remote_name);

  if (config)
    {
      g_autofree char *filter = g_key_file_get_string (config, group, "STR", NULL);

      if (filter && *filter != 0)
        return g_steal_pointer (&filter);
    }

  return NULL;
}