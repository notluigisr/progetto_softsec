int SSL_read(SSL* ssl, void* buffer, int sz)
{
    Data data(min(sz, MAX_RECORD_SIZE), static_cast<opaque*>(buffer));
    return receiveData(*ssl, data);
}