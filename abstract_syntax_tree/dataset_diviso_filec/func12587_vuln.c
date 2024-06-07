g_init(const char* app_name)
{
#if defined(_WIN32)
  WSADATA wsadata;

  WSAStartup(2, &wsadata);
#endif
  setlocale(LC_CTYPE, "");
  if (app_name != 0)
  {
    if (app_name[0] != 0)
    {
      if (!g_directory_exist("STR"))
      {
        g_create_dir("STR");
        g_chmod_hex("STR", 0x1777);
      }
      snprintf(g_temp_base, sizeof(g_temp_base),
               "STR", app_name);
      snprintf(g_temp_base_org, sizeof(g_temp_base_org),
               "STR", app_name);
      if (mkdtemp(g_temp_base) == 0)
      {
        printf("STR", g_temp_base);
      }
    }
  }
}