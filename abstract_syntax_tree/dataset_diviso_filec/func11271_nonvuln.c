static int check_dane_pkeys(X509_STORE_CTX *ctx)
{
    SSL_DANE *dane = ctx->dane;
    danetls_record *t;
    int num = ctx->num_untrusted;
    X509 *cert = sk_X509_value(ctx->chain, num - 1);
    int recnum = sk_danetls_record_num(dane->trecs);
    int i;

    for (i = 0; i < recnum; ++i) {
        t = sk_danetls_record_value(dane->trecs, i);
        if (t->usage != DANETLS_USAGE_DANE_TA ||
            t->selector != DANETLS_SELECTOR_SPKI ||
            t->mtype != DANETLS_MATCHING_FULL ||
            X509_verify(cert, t->spki) <= 0)
            continue;

        
        X509_free(dane->mcert);
        dane->mcert = NULL;

        
        ctx->bare_ta_signed = 1;
        dane->mdpth = num - 1;
        dane->mtlsa = t;

        
        num = sk_X509_num(ctx->chain);
        for (; num > ctx->num_untrusted; --num)
            X509_free(sk_X509_pop(ctx->chain));

        return X509_TRUST_TRUSTED;
    }

    return X509_TRUST_UNTRUSTED;
}