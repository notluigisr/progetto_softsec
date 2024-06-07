static int check_cert_usable(SSL *s, const SIGALG_LOOKUP *sig, X509 *x,
                             EVP_PKEY *pkey)
{
    const SIGALG_LOOKUP *lu;
    int mdnid, pknid, supported;
    size_t i;

    
    ERR_set_mark();
    supported = EVP_PKEY_supports_digest_nid(pkey, sig->hash);
    ERR_pop_to_mark();
    if (supported == 0)
        return 0;

    
    if (s->s3.tmp.peer_cert_sigalgs != NULL) {
        if (!X509_get_signature_info(x, &mdnid, &pknid, NULL, NULL))
            return 0;
        for (i = 0; i < s->s3.tmp.peer_cert_sigalgslen; i++) {
            lu = tls1_lookup_sigalg(s->s3.tmp.peer_cert_sigalgs[i]);
            if (lu == NULL)
                continue;

            
            if (mdnid == lu->hash && pknid == lu->sig)
                return 1;
        }
        return 0;
    }

    
    return 1;
}