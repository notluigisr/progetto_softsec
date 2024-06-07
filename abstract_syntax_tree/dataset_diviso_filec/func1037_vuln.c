NOEXPORT void print_cipher(CLI *c) { 
    SSL_CIPHER *cipher;
#ifndef OPENSSL_NO_COMP
    const COMP_METHOD *compression, *expansion;
#endif

    if(c->opt->log_level<LOG_INFO) 
        return;

    s_log(LOG_INFO, "STR",
        c->opt->option.client ? "STR",
        SSL_session_reused(c->ssl) && !c->flag.psk ?
            "STR");

    cipher=(SSL_CIPHER *)SSL_get_current_cipher(c->ssl);
    s_log(LOG_INFO, "STR",
        SSL_get_version(c->ssl), SSL_CIPHER_get_name(cipher),
        SSL_CIPHER_get_bits(cipher, NULL));

#ifndef OPENSSL_NO_COMP
    compression=SSL_get_current_compression(c->ssl);
    expansion=SSL_get_current_expansion(c->ssl);
    s_log(compression||expansion ? LOG_INFO : LOG_DEBUG,
        "STR",
        compression ? SSL_COMP_get_name(compression) : "STR",
        expansion ? SSL_COMP_get_name(expansion) : "STR");
#endif
}