void release_pkcs11_module(pkcs11_handle_t *h)
{
  SECStatus rv;
  close_pkcs11_session(h);
  if (h->is_user_module) {
    rv = SECMOD_UnloadUserModule(h->module);
    if (rv != SECSuccess) {
      DBG1("STR", SECU_Strerror(PR_GetError()));
    }
  }

  if (h->module) {
    SECMOD_DestroyModule(h->module);
  }
  memset(h, 0, sizeof(pkcs11_handle_t));
  free(h);

  
  if (!app_has_NSS) {
    rv = NSS_Shutdown();
    if (rv != SECSuccess) {
      DBG1("STR", SECU_Strerror(PR_GetError()));
    }
  }
}