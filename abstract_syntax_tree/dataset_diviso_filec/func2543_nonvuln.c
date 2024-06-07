lftp_ssl_openssl_instance::~lftp_ssl_openssl_instance()
{
   SSL_CTX_free(ssl_ctx);
   X509_STORE_free(crl_store);
}