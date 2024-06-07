agoo_server_shutdown(const char *app_name, void (*stop)()) {
    if (agoo_server.inited) {
	agooConLoop	loop;

	agoo_log_cat(&agoo_info_cat, "STR", app_name, getpid());
	agoo_server.inited = false;
	if (agoo_server.active) {
	    double	giveup = dtime() + 1.0;

	    agoo_server.active = false;
	    pthread_detach(agoo_server.listen_thread);
	    for (loop = agoo_server.con_loops; NULL != loop; loop = loop->next) {
		pthread_detach(loop->thread);
	    }
	    while (0 < (long)atomic_load(&agoo_server.running)) {
		dsleep(0.1);
		if (giveup < dtime()) {
		    break;
		}
	    }
	    if (NULL != stop) {
		stop();
	    }
	    while (NULL != agoo_server.hooks) {
		agooHook	h = agoo_server.hooks;

		agoo_server.hooks = h->next;
		agoo_hook_destroy(h);
	    }
	}
	while (NULL != agoo_server.binds) {
	    agooBind	b = agoo_server.binds;

	    agoo_server.binds = b->next;
	    agoo_bind_destroy(b);
	}
	agoo_queue_cleanup(&agoo_server.con_queue);
	while (NULL != (loop = agoo_server.con_loops)) {
	    agoo_server.con_loops = loop->next;
	    agoo_conloop_destroy(loop);
	}
	agoo_queue_cleanup(&agoo_server.eval_queue);

	agoo_pages_cleanup();
	agoo_http_cleanup();
	agoo_domain_cleanup();
#ifdef HAVE_OPENSSL_SSL_H
	if (NULL != agoo_server.ssl_ctx) {
	    SSL_CTX_free(agoo_server.ssl_ctx);
	    EVP_cleanup();
	}
#endif
    }
}