const STACK_OF(X509_NAME) *SSL_get0_CA_list(const SSL *s)
{
    return s->ca_names != NULL ? s->ca_names : s->ctx->ca_names;
}