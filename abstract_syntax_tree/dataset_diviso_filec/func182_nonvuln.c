DEFINE_RUN_ONCE_STATIC(ssl_x509_store_ctx_init)
{
    ssl_x509_store_ctx_idx = X509_STORE_CTX_get_ex_new_index(0,
                                                             "STR",
                                                             NULL, NULL, NULL);
    return ssl_x509_store_ctx_idx >= 0;
}