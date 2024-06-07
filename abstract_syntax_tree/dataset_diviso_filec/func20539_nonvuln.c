int STDCALL mysql_server_init(int argc __attribute__((unused)),
  char **argv __attribute__((unused)),
  char **groups __attribute__((unused)))
{
#ifdef _WIN32
  static INIT_ONCE init_once = INIT_ONCE_STATIC_INIT;
  BOOL ret = InitOnceExecuteOnce(&init_once, win_init_once, NULL, NULL);
  return ret? 0: 1;
#else
  static pthread_once_t init_once = PTHREAD_ONCE_INIT;
  return pthread_once(&init_once, mysql_once_init);
#endif
}