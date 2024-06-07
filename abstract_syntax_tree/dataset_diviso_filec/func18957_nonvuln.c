int main(int argc, char *argv[])
{
  int res;
  struct Configurable config;

  memset(&config, 0, sizeof(struct Configurable));

  config.errors = stderr; 

  checkfds();

  res = operate(&config, argc, argv);
  free_config_fields(&config);

#ifdef __NOVELL_LIBC__
  pressanykey();
#endif
#ifdef  VMS
  if (res > CURL_LAST) res = CURL_LAST; 
  return (vms_cond[res]|vms_show);      
#else
  return res;
#endif
}