MSG_PROCESS_RETURN dtls_process_hello_verify(SSL *s, PACKET *pkt)
{
    size_t cookie_len;
    PACKET cookiepkt;

    if (!PACKET_forward(pkt, 2)
        || !PACKET_get_length_prefixed_1(pkt, &cookiepkt)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_R_LENGTH_MISMATCH);
        return MSG_PROCESS_ERROR;
    }

    cookie_len = PACKET_remaining(&cookiepkt);
    if (cookie_len > sizeof(s->d1->cookie)) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_R_LENGTH_TOO_LONG);
        return MSG_PROCESS_ERROR;
    }

    if (!PACKET_copy_bytes(&cookiepkt, s->d1->cookie, cookie_len)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_R_LENGTH_MISMATCH);
        return MSG_PROCESS_ERROR;
    }
    s->d1->cookie_len = cookie_len;

    return MSG_PROCESS_FINISHED_READING;
}