int tls1_process_sigalgs(SSL *s)
{
    size_t i;
    uint32_t *pvalid = s->s3.tmp.valid_flags;

    if (!tls1_set_shared_sigalgs(s))
        return 0;

    for (i = 0; i < SSL_PKEY_NUM; i++)
        pvalid[i] = 0;

    for (i = 0; i < s->shared_sigalgslen; i++) {
        const SIGALG_LOOKUP *sigptr = s->shared_sigalgs[i];
        int idx = sigptr->sig_idx;

        
        if (SSL_IS_TLS13(s) && sigptr->sig == EVP_PKEY_RSA)
            continue;
        
        if (pvalid[idx] == 0 && !ssl_cert_is_disabled(idx))
            pvalid[idx] = CERT_PKEY_EXPLICIT_SIGN | CERT_PKEY_SIGN;
    }
    return 1;
}