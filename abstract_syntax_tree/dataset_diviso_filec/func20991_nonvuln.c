static int tls_construct_cke_rsa(SSL *s, WPACKET *pkt)
{
    unsigned char *encdata = NULL;
    EVP_PKEY *pkey = NULL;
    EVP_PKEY_CTX *pctx = NULL;
    size_t enclen;
    unsigned char *pms = NULL;
    size_t pmslen = 0;

    if (s->session->peer == NULL) {
        
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    pkey = X509_get0_pubkey(s->session->peer);
    if (!EVP_PKEY_is_a(pkey, "STR")) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    pmslen = SSL_MAX_MASTER_KEY_LENGTH;
    pms = OPENSSL_malloc(pmslen);
    if (pms == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    pms[0] = s->client_version >> 8;
    pms[1] = s->client_version & 0xff;
    if (RAND_bytes_ex(s->ctx->libctx, pms + 2, pmslen - 2, 0) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    
    if (s->version > SSL3_VERSION && !WPACKET_start_sub_packet_u16(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, ERR_R_INTERNAL_ERROR);
        goto err;
    }

    pctx = EVP_PKEY_CTX_new_from_pkey(s->ctx->libctx, pkey, s->ctx->propq);
    if (pctx == NULL || EVP_PKEY_encrypt_init(pctx) <= 0
        || EVP_PKEY_encrypt(pctx, NULL, &enclen, pms, pmslen) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, ERR_R_EVP_LIB);
        goto err;
    }
    if (!WPACKET_allocate_bytes(pkt, enclen, &encdata)
            || EVP_PKEY_encrypt(pctx, encdata, &enclen, pms, pmslen) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_R_BAD_RSA_ENCRYPT);
        goto err;
    }
    EVP_PKEY_CTX_free(pctx);
    pctx = NULL;

    
    if (s->version > SSL3_VERSION && !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, ERR_R_INTERNAL_ERROR);
        goto err;
    }

    
    if (!ssl_log_rsa_client_key_exchange(s, encdata, enclen, pms, pmslen)) {
        
        goto err;
    }

    s->s3.tmp.pms = pms;
    s->s3.tmp.pmslen = pmslen;

    return 1;
 err:
    OPENSSL_clear_free(pms, pmslen);
    EVP_PKEY_CTX_free(pctx);

    return 0;
}