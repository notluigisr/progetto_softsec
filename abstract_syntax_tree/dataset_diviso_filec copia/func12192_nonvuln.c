flatpak_run_get_pulse_home (void)
{
  
  {
    const char *parent = g_get_home_dir ();
    g_autofree char *ret = g_build_filename (parent, "STR", NULL);

    if (g_file_test (ret, G_FILE_TEST_IS_DIR))
      return g_steal_pointer (&ret);
  }

  
  {
    const char *parent = g_get_user_config_dir ();
    
    g_autofree char *ret = g_build_filename (parent, "STR", NULL);

    if (g_file_test (ret, G_FILE_TEST_IS_DIR))
      return g_steal_pointer (&ret);
  }

  return NULL;
}