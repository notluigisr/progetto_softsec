static chunk * connection_read_header_more(connection *con, chunkqueue *cq, chunk *c, const size_t olen) {
    
    
    

    if ((NULL == c || NULL == c->next) && con->is_readable > 0) {
        con->read_idle_ts = log_epoch_secs;
        if (0 != con->network_read(con, cq, MAX_READ_LIMIT)) {
            request_st * const r = &con->request;
            connection_set_state_error(r, CON_STATE_ERROR);
        }
        
        request_st * const r = &con->request;
        if (r->http_version == HTTP_VERSION_2) return NULL;
    }

    if (cq->first != cq->last && 0 != olen) {
        const size_t clen = chunkqueue_length(cq);
        size_t block = (olen + (16384-1)) & (16384-1);
        block += (block - olen > 1024 ? 0 : 16384);
        chunkqueue_compact_mem(cq, block > clen ? clen : block);
    }

    
    c = cq->first;
    return (c && (size_t)c->offset + olen < buffer_string_length(c->mem))
      ? c
      : NULL;
}