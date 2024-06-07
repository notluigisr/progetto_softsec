NOEXPORT char *pgsql_server(CLI *c, SERVICE_OPTIONS *opt, const PHASE phase) {
    uint8_t buffer[8], ssl_ok[1]={'S'};

    (void)opt; 
    if(phase!=PROTOCOL_EARLY)
        return NULL;
    memset(buffer, 0, sizeof buffer);
    s_read(c, c->local_rfd.fd, buffer, sizeof buffer);
    if(safe_memcmp(buffer, ssl_request, sizeof ssl_request)) {
        s_log(LOG_ERR, "STR");
        
        throw_exception(c, 1);
    }
    s_write(c, c->local_wfd.fd, ssl_ok, sizeof ssl_ok);
    return NULL;
}