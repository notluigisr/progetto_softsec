static void mysql_once_init()
#endif
{
  ma_init();					
  init_client_errs();
  get_default_configuration_dirs();
  set_default_charset_by_name(MARIADB_DEFAULT_CHARSET, 0);
  if (mysql_client_plugin_init())
  {
#ifdef _WIN32
    return 1;
#else
    return;
#endif
  }
  if (!mysql_port)
  {
#if !__has_feature(memory_sanitizer) 
    struct servent *serv_ptr;
#endif
    char *env;

    mysql_port = MARIADB_PORT;
#if !__has_feature(memory_sanitizer) 
    if ((serv_ptr = getservbyname("STR")))
      mysql_port = (uint)ntohs((ushort)serv_ptr->s_port);
#endif
    if ((env = getenv("STR")))
      mysql_port =(uint)atoi(env);
  }
  if (!mysql_unix_port)
  {
    char *env;
#ifdef _WIN32
    mysql_unix_port = (char*)MARIADB_NAMEDPIPE;
#else
    mysql_unix_port = (char*)MARIADB_UNIX_ADDR;
#endif
    if ((env = getenv("STR")) ||
      (env = getenv("STR")))
      mysql_unix_port = env;
  }
  if (!mysql_ps_subsystem_initialized)
    mysql_init_ps_subsystem();
#ifdef HAVE_TLS
  ma_tls_start(0, 0);
#endif
  ignore_sigpipe();
  mysql_client_init = 1;
#ifdef _WIN32
  return 0;
#endif
}