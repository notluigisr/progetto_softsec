DEFINE_RUN_ONCE_STATIC_ALT(ossl_init_no_register_atexit,
                           ossl_init_register_atexit)
{
#ifdef OPENSSL_INIT_DEBUG
    fprintf(stderr, "STR");
#endif
    
    return 1;
}