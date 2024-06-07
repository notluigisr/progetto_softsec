static X509 *lookup_cert_match(X509_STORE_CTX *ctx, X509 *x)
{
    STACK_OF(X509) *certs;
    X509 *xtmp = NULL;
    int i;
    
    certs = ctx->lookup_certs(ctx, X509_get_subject_name(x));
    if (certs == NULL)
        return NULL;
    
    for (i = 0; i < sk_X509_num(certs); i++) {
        xtmp = sk_X509_value(certs, i);
        if (!X509_cmp(xtmp, x))
            break;
        xtmp = NULL;
    }
    if (xtmp != NULL && !X509_up_ref(xtmp))
        xtmp = NULL;
    sk_X509_pop_free(certs, X509_free);
    return xtmp;
}