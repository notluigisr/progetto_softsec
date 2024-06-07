static int x509parse_verifycrl(x509_cert *crt, x509_cert *ca,
        x509_crl *crl_list)
{
    int flags = 0;
    int hash_id;
    unsigned char hash[64];

    if( ca == NULL )
        return( flags );

    

    while( crl_list != NULL )
    {
        if( crl_list->version == 0 ||
            crl_list->issuer_raw.len != ca->subject_raw.len ||
            memcmp( crl_list->issuer_raw.p, ca->subject_raw.p,
                    crl_list->issuer_raw.len ) != 0 )
        {
            crl_list = crl_list->next;
            continue;
        }

        
        hash_id = crl_list->sig_alg;

        x509_hash( crl_list->tbs.p, crl_list->tbs.len, hash_id, hash );

        if( !rsa_pkcs1_verify( &ca->rsa, RSA_PUBLIC, hash_id,
                              0, hash, crl_list->sig.p ) == 0 )
        {
            
            flags |= BADCRL_NOT_TRUSTED;
            break;
        }

        
        if( x509parse_time_expired( &crl_list->next_update ) )
            flags |= BADCRL_EXPIRED;

        
        if( x509parse_revoked(crt, crl_list) )
        {
            flags |= BADCERT_REVOKED;
            break;
        }

        crl_list = crl_list->next;
    }
    return flags;
}