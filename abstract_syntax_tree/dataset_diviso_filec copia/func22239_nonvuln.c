MONGO_EXPORT int mongo_connect( mongo *conn , const char *host, int port ) {
    int ret;
    bson_errprintf("STR");
    ret = mongo_client( conn, host, port );
    mongo_set_write_concern( conn, 0 );
    return ret;
}