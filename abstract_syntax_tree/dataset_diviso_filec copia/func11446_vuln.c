static void ssl_reset_sock_state(pj_ssl_sock_t *ssock)
{
    ossl_sock_t *ossock = (ossl_sock_t *)ssock;
    
    if (ossock->ossl_ssl && SSL_in_init(ossock->ossl_ssl) == 0) {
	int ret = SSL_shutdown(ossock->ossl_ssl);
	if (ret == 0) {
	    
	    flush_circ_buf_output(ssock, &ssock->shutdown_op_key, 0, 0);
	}
    }

    pj_lock_acquire(ssock->write_mutex);
    ssock->ssl_state = SSL_STATE_NULL;
    pj_lock_release(ssock->write_mutex);

    ssl_close_sockets(ssock);

    
    ERR_clear_error();
}