static int has_usable_cert(SSL *s, const SIGALG_LOOKUP *sig, int idx)
{
    const SIGALG_LOOKUP *lu;
    int mdnid, pknid, supported;
    size_t i;

    
    if (idx == -1)
        idx = sig->sig_idx;
    if (!ssl_has_cert(s, idx))
        return 0;
    if (s->s3.tmp.peer_cert_sigalgs != NULL) {
        for (i = 0; i < s->s3.tmp.peer_cert_sigalgslen; i++) {
            lu = tls1_lookup_sigalg(s->s3.tmp.peer_cert_sigalgs[i]);
            if (lu == NULL
                || !X509_get_signature_info(s->cert->pkeys[idx].x509, &mdnid,
                                            &pknid, NULL, NULL)
                
                || mdnid != lu->hash
                || pknid != lu->sig)
                continue;

            ERR_set_mark();
            supported = EVP_PKEY_supports_digest_nid(s->cert->pkeys[idx].privatekey,
                                                     mdnid);
            if (supported == 0)
                continue;
            else if (supported < 0)
            {
                
                ERR_pop_to_mark();
            }
            return 1;
        }
        return 0;
    }
    supported = EVP_PKEY_supports_digest_nid(s->cert->pkeys[idx].privatekey,
                                             sig->hash);
    if (supported == 0)
        return 0;
    else if (supported < 0)
        ERR_clear_error();

    return 1;
}