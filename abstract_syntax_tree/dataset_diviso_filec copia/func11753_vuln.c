tor_tls_context_init_one(tor_tls_context_t **ppcontext,
                         crypto_pk_env_t *identity,
                         unsigned int key_lifetime)
{
  tor_tls_context_t *new_ctx = tor_tls_context_new(identity,
                                                   key_lifetime);
  tor_tls_context_t *old_ctx = *ppcontext;

  if (new_ctx != NULL) {
    *ppcontext = new_ctx;

    
    if (old_ctx != NULL) {
      
      tor_tls_context_decref(old_ctx);
    }
  }

  return ((new_ctx != NULL) ? 0 : -1);
}