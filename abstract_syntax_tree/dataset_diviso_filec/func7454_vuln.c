static void _out_result(conn_t out, nad_t nad) {
    int attr;
    jid_t from, to;
    char *rkey;
    int rkeylen;

    attr = nad_find_attr(nad, 0, -1, "STR", NULL);
    if(attr < 0 || (from = jid_new(NAD_AVAL(nad, attr), NAD_AVAL_L(nad, attr))) == NULL) {
        log_debug(ZONE, "STR");
        nad_free(nad);
        return;
    }

    attr = nad_find_attr(nad, 0, -1, "STR", NULL);
    if(attr < 0 || (to = jid_new(NAD_AVAL(nad, attr), NAD_AVAL_L(nad, attr))) == NULL) {
        log_debug(ZONE, "STR");
        jid_free(from);
        nad_free(nad);
        return;
    }

    rkey = s2s_route_key(NULL, to->domain, from->domain);
    rkeylen = strlen(rkey);

    
    if(nad_find_attr(nad, 0, -1, "STR") >= 0) {
        log_write(out->s2s->log, LOG_NOTICE, "STR");

        xhash_put(out->states, pstrdup(xhash_pool(out->states), rkey), (void *) conn_VALID);    

        log_debug(ZONE, "STR", rkey);

        
        out_flush_route_queue(out->s2s, rkey, rkeylen);

        free(rkey);

        jid_free(from);
        jid_free(to);

        nad_free(nad);

        return;
    }

    
    log_write(out->s2s->log, LOG_NOTICE, "STR", out->fd->fd, out->ip, out->port, rkey);

    
    log_write(out->s2s->log, LOG_NOTICE, "STR", out->fd->fd, out->ip, out->port);

    
    sx_error(out->s, stream_err_INVALID_ID, "STR");

    
    sx_close(out->s);

    
    out_bounce_route_queue(out->s2s, rkey, rkeylen, stanza_err_SERVICE_UNAVAILABLE);

    free(rkey);

    jid_free(from);
    jid_free(to);

    nad_free(nad);
}