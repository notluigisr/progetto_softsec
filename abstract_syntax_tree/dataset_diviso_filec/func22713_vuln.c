static int ossl_init(void)
{
#if (OPENSSL_VERSION_NUMBER >= 0x10100000L) &&  \
  !defined(LIBRESSL_VERSION_NUMBER)
  const uint64_t flags =
#ifdef OPENSSL_INIT_ENGINE_ALL_BUILTIN
    
    OPENSSL_INIT_ENGINE_ALL_BUILTIN |
#endif
#ifdef CURL_DISABLE_OPENSSL_AUTO_LOAD_CONFIG
    OPENSSL_INIT_NO_LOAD_CONFIG |
#else
    OPENSSL_INIT_LOAD_CONFIG |
#endif
    0;
  OPENSSL_init_ssl(flags, NULL);
#else
  OPENSSL_load_builtin_modules();

#ifdef USE_OPENSSL_ENGINE
  ENGINE_load_builtin_engines();
#endif


#ifndef CONF_MFLAGS_DEFAULT_SECTION

#endif

#ifndef CURL_DISABLE_OPENSSL_AUTO_LOAD_CONFIG
  CONF_modules_load_file(NULL, NULL,
                         CONF_MFLAGS_DEFAULT_SECTION|
                         CONF_MFLAGS_IGNORE_MISSING_FILE);
#endif

  
  SSL_load_error_strings();

  
  if(!SSLeay_add_ssl_algorithms())
    return 0;

  OpenSSL_add_all_algorithms();
#endif

  Curl_tls_keylog_open();

  
  if(ossl_get_ssl_data_index() < 0 || ossl_get_ssl_conn_index() < 0 ||
     ossl_get_ssl_sockindex_index() < 0)
    return 0;

  return 1;
}