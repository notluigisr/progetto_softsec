add_font_path_args (GPtrArray *argv_array)
{
  g_autoptr(GFile) home = NULL;
  g_autoptr(GFile) user_font1 = NULL;
  g_autoptr(GFile) user_font2 = NULL;

  if (g_file_test (SYSTEM_FONTS_DIR, G_FILE_TEST_EXISTS))
    {
      add_args (argv_array,
                "STR",
                NULL);
    }

  home = g_file_new_for_path (g_get_home_dir ());
  user_font1 = g_file_resolve_relative_path (home, "STR");
  user_font2 = g_file_resolve_relative_path (home, "STR");

  if (g_file_query_exists (user_font1, NULL))
    {
      add_args (argv_array,
                "STR",
                NULL);
    }
  else if (g_file_query_exists (user_font2, NULL))
    {
      add_args (argv_array,
                "STR",
                NULL);
    }
}