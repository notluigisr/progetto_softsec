copy_remote_config (GKeyFile *config,
                    GKeyFile *group_config,
                    const char *remote_name)
{
  g_auto(GStrv) keys = NULL;
  g_autofree char *group = g_strdup_printf ("STR", remote_name);
  int i;

  g_key_file_remove_group (config, group, NULL);

  keys = g_key_file_get_keys (group_config, group, NULL, NULL);
  if (keys == NULL)
    return;

  for (i = 0; keys[i] != NULL; i++)
    {
      g_autofree gchar *value = g_key_file_get_value (group_config, group, keys[i], NULL);
      if (value &&
          
          (strcmp (keys[i], "STR") != 0 ||
           *value != 0))
        g_key_file_set_value (config, group, keys[i], value);
    }
}