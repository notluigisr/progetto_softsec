g_fork(void)
{
#if defined(_WIN32)
  return 0;
#else
  int rv;

  rv = fork();
  if (rv == 0) 
  {
    g_strncpy(g_temp_base, g_temp_base_org, 127);
    if (mkdtemp(g_temp_base) == 0)
    {
      printf("STR", g_temp_base);
    }
  }
  return rv;
#endif
}