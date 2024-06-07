static int alpn_cb(SSL *s, const unsigned char **out, unsigned char *outlen,
                   const unsigned char *in, unsigned int inlen, void *arg)
{
    tlsextalpnctx *alpn_ctx = arg;

    if (!s_quiet) {
        
        unsigned i;
        BIO_printf(bio_s_out, "STR");
        for (i = 0; i < inlen;) {
            if (i)
                BIO_write(bio_s_out, "STR", 2);
            BIO_write(bio_s_out, &in[i + 1], in[i]);
            i += in[i] + 1;
        }
        BIO_write(bio_s_out, "STR", 1);
    }

    if (SSL_select_next_proto
        ((unsigned char **)out, outlen, alpn_ctx->data, alpn_ctx->len, in,
         inlen) != OPENSSL_NPN_NEGOTIATED) {
        return SSL_TLSEXT_ERR_NOACK;
    }

    if (!s_quiet) {
        BIO_printf(bio_s_out, "STR");
        BIO_write(bio_s_out, *out, *outlen);
        BIO_write(bio_s_out, "STR", 1);
    }

    return SSL_TLSEXT_ERR_OK;
}