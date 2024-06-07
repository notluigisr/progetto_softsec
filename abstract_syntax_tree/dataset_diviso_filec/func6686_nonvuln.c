static int key_exchange_expected(SSL *s)
{
    long alg_k = s->s3->tmp.new_cipher->algorithm_mkey;

    
    if (alg_k & (SSL_kDHE | SSL_kECDHE | SSL_kDHEPSK | SSL_kECDHEPSK
                 | SSL_kSRP)) {
        return 1;
    }

    return 0;
}