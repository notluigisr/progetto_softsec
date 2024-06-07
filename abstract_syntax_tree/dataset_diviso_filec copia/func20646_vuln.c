NOEXPORT int dh_init(SERVICE_OPTIONS *section) {
    DH *dh=NULL;
    int i, n;
    char description[128];
    STACK_OF(SSL_CIPHER) *ciphers;

    section->option.dh_temp_params=0; 

    
    ciphers=SSL_CTX_get_ciphers(section->ctx);
    if(!ciphers)
        return 1; 
    n=sk_SSL_CIPHER_num(ciphers);
    for(i=0; i<n; ++i) {
        *description='\0';
        SSL_CIPHER_description(sk_SSL_CIPHER_value(ciphers, i),
            description, sizeof description);
        
        if(strstr(description, "STR")) {
            s_log(LOG_INFO, "STR",
                SSL_CIPHER_get_name(sk_SSL_CIPHER_value(ciphers, i)));
            break;
        }
    }
    if(i==n) { 
        s_log(LOG_INFO, "STR");
        return 0; 
    }

    s_log(LOG_DEBUG, "STR");
#ifndef OPENSSL_NO_ENGINE
    if(!section->engine) 
#endif
        dh=dh_read(section->cert);
    if(dh) {
        SSL_CTX_set_tmp_dh(section->ctx, dh);
        s_log(LOG_INFO, "STR", 8*DH_size(dh));
        DH_free(dh);
        return 0; 
    }
    CRYPTO_THREAD_read_lock(stunnel_locks[LOCK_DH]);
    SSL_CTX_set_tmp_dh(section->ctx, dh_params);
    CRYPTO_THREAD_unlock(stunnel_locks[LOCK_DH]);
    dh_temp_params=1; 
    section->option.dh_temp_params=1; 
    s_log(LOG_INFO, "STR");
    return 0; 
}