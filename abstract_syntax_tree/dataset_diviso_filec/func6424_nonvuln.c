int SSL_get_error(SSL* ssl, int )
{
    return ssl->getStates().What();
}