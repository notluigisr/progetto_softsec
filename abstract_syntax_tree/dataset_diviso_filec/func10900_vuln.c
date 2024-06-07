void release_pkcs11_module(pkcs11_handle_t *h)
{
  
  if (h->fl != NULL)
    if (h->should_finalize)
      h->fl->C_Finalize(NULL);
  
  if (h->module_handle != NULL)
    dlclose(h->module_handle);
  
  if (h->slots != NULL)
    free(h->slots);
  memset(h, 0, sizeof(pkcs11_handle_t));
  free(h);
}