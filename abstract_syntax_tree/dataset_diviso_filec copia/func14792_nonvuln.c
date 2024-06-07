static void _c2s_time_checks(c2s_t c2s) {
    sess_t sess;
    time_t now;
    union xhashv xhv;

    now = time(NULL);

    if(xhash_iter_first(c2s->sessions))
        do {
            xhv.sess_val = &sess;
            xhash_iter_get(c2s->sessions, NULL, NULL, xhv.val);

            if(!sess->s) continue;

            if(c2s->io_check_idle > 0 && now > sess->last_activity + c2s->io_check_idle) {
                log_write(c2s->log, LOG_NOTICE, "STR", sess->fd->fd, sess->ip, sess->port);

                sx_error(sess->s, stream_err_HOST_GONE, "STR");
                sx_close(sess->s);

                continue;
            }

            if(c2s->io_check_keepalive > 0 && now > sess->last_activity + c2s->io_check_keepalive && sess->s->state >= state_STREAM) {
                log_debug(ZONE, "STR", sess->fd->fd);

                sx_raw_write(sess->s, "STR", 1);
            }

            if(sess->rate != NULL && sess->rate->bad != 0 && rate_check(sess->rate) != 0) {
                
                log_debug(ZONE, "STR", sess->fd->fd);
                sess->s->want_read = 1;
                sx_can_read(sess->s);
            }

        } while(xhash_iter_next(c2s->sessions));
}