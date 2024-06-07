static void tstream_tls_pull_done(struct tevent_req *subreq)
{
	struct tstream_context *stream =
		tevent_req_callback_data(subreq,
		struct tstream_context);
	struct tstream_tls *tlss =
		tstream_context_data(stream,
		struct tstream_tls);
	int ret;
	int sys_errno;

	tlss->pull.subreq = NULL;

	ret = tstream_readv_recv(subreq, &sys_errno);
	TALLOC_FREE(subreq);
	if (ret == -1) {
		tlss->error = sys_errno;
		tstream_tls_retry(stream, false);
		return;
	}

	tstream_tls_retry(stream, false);
}