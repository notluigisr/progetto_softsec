NOEXPORT void cache_remove(SSL_CTX *ctx, SSL_SESSION *sess) {
    const unsigned char *session_id;
    unsigned int session_id_length;

    session_id=SSL_SESSION_get_id(sess, &session_id_length);
    cache_transfer(ctx, CACHE_CMD_REMOVE, 0,
        session_id, session_id_length, NULL, 0, NULL, NULL);
}