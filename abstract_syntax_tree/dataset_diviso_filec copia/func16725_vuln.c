static int check_purpose(X509_STORE_CTX *ctx, X509 *x, int purpose, int depth,
                         int must_be_ca)
{
    int pu_ok = X509_check_purpose(x, purpose, must_be_ca > 0);
    int tr_ok = X509_TRUST_UNTRUSTED;

    
    if (depth >= ctx->num_untrusted && purpose == ctx->param->purpose)
        tr_ok = X509_check_trust(x, ctx->param->trust, X509_TRUST_NO_SS_COMPAT);

    if (tr_ok != X509_TRUST_REJECTED &&
        (pu_ok == 1 ||
         (pu_ok != 0 && (ctx->param->flags & X509_V_FLAG_X509_STRICT) == 0)))
        return 1;

    ctx->error = X509_V_ERR_INVALID_PURPOSE;
    ctx->error_depth = depth;
    ctx->current_cert = x;
    return ctx->verify_cb(0, ctx);
}