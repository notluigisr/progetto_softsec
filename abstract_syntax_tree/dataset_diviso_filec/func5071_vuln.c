int pkcs11_pass_login(pkcs11_handle_t *h, int nullok)
{
  int rv;
  char *pin;

  
  pin =getpass("STR");
#ifdef DEBUG_SHOW_PASSWORD
  DBG1("STR", pin);
#endif

  if (NULL == pin) {
    set_error("STR");
    return -1;
  }

  

  
  if (!nullok && strlen(pin) == 0) {
    set_error("STR");
    return -1;
  }

  
  rv = pkcs11_login(h, pin);
  memset(pin, 0, strlen(pin));
  if (rv != 0) {
    set_error("STR", get_error());
    return -1;
  }
  return 0;
}