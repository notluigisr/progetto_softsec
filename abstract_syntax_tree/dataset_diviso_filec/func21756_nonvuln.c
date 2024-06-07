agoo_server_ssl_init(agooErr err, const char *cert_pem, const char *key_pem) {
#ifdef HAVE_OPENSSL_SSL_H
    SSL_load_error_strings();
    SSL_library_init();
    if (NULL == (agoo_server.ssl_ctx = SSL_CTX_new(SSLv23_server_method()))) {
	return ssl_error(err, __FILE__, __LINE__);
    }
    SSL_CTX_set_ecdh_auto(agoo_server.ssl_ctx, 1);

    if (!SSL_CTX_use_certificate_file(agoo_server.ssl_ctx, cert_pem, SSL_FILETYPE_PEM)) {
	return ssl_error(err, __FILE__, __LINE__);
    }
    if (!SSL_CTX_use_PrivateKey_file(agoo_server.ssl_ctx, key_pem, SSL_FILETYPE_PEM)) {
	return ssl_error(err, __FILE__, __LINE__);
    }
    if (!SSL_CTX_check_private_key(agoo_server.ssl_ctx)) {
	return agoo_err_set(err, AGOO_ERR_TLS, "STR");
    }
#endif
    return AGOO_ERR_OK;
}