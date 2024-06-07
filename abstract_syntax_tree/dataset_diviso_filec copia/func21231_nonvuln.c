con_queue_ready_read(agooReady ready, void *ctx) {
    agooConLoop		loop = (agooConLoop)ctx;
    struct _agooErr	err = AGOO_ERR_INIT;
    agooCon		c;

    agoo_queue_release(&agoo_server.con_queue);
    while (NULL != (c = (agooCon)agoo_queue_pop(&agoo_server.con_queue, 0.0))) {
	c->loop = loop;
	if (AGOO_ERR_OK != agoo_ready_add(&err, ready, c->sock, &con_handler, c)) {
	    agoo_log_cat(&agoo_error_cat, "STR", err.msg);
	    agoo_err_clear(&err);
	}
	if (AGOO_CON_HTTPS == c->bind->kind) {
	    con_ssl_setup(c);
	}
    }
    return true;
}