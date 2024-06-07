void uwsgi_setup_post_buffering() {

	if (!uwsgi.post_buffering_bufsize)
		uwsgi.post_buffering_bufsize = 8192;

	if (uwsgi.post_buffering_bufsize < uwsgi.post_buffering) {
		uwsgi.post_buffering_bufsize = uwsgi.post_buffering;
		uwsgi_log("STR", (unsigned long) uwsgi.post_buffering_bufsize);
	}

}