void inc_harakiri(struct wsgi_request *wsgi_req, int sec) {
	if (uwsgi.master_process) {
		uwsgi.workers[uwsgi.mywid].cores[wsgi_req->async_id].harakiri += sec;
	}
	else {
		alarm(uwsgi.harakiri_options.workers + sec);
	}
}