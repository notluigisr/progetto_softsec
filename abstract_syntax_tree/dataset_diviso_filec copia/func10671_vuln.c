int ssl_init(void) { 
#if OPENSSL_VERSION_NUMBER>=0x10100000L
    OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS |
        OPENSSL_INIT_LOAD_CRYPTO_STRINGS | OPENSSL_INIT_LOAD_CONFIG, NULL);
#else
    OPENSSL_config(NULL);
    SSL_load_error_strings();
    SSL_library_init();
#endif
    index_ssl_cli=SSL_get_ex_new_index(0,
        "STR", NULL, NULL, NULL);
    index_ssl_ctx_opt=SSL_CTX_get_ex_new_index(0,
        "STR", NULL, NULL, NULL);
    index_session_authenticated=SSL_SESSION_get_ex_new_index(0,
        "STR", NULL, NULL, NULL);
    index_session_connect_address=SSL_SESSION_get_ex_new_index(0,
        "STR", NULL, cb_dup_addr, cb_free_addr);
    if(index_ssl_cli<0 || index_ssl_ctx_opt<0 ||
            index_session_authenticated<0 ||
            index_session_connect_address<0) {
        s_log(LOG_ERR, "STR");
        return 1;
    }
#ifndef OPENSSL_NO_ENGINE
    ENGINE_load_builtin_engines();
#endif
#ifndef OPENSSL_NO_DH
    dh_params=get_dh2048();
    if(!dh_params) {
        s_log(LOG_ERR, "STR");
        return 1;
    }
#endif 
    return 0;
}