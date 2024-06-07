static void wait_for_child_to_die(void *ctx)
{
	REQUEST *request = ctx;

	rad_assert(request->magic == REQUEST_MAGIC);

	
	if ((request->child_state == REQUEST_QUEUED) ||
	    ((request->child_state == REQUEST_RUNNING) &&
	     (pthread_equal(request->child_pid, NO_SUCH_CHILD_PID) == 0))) {

		
		if (request->delay < (USEC * 60 * 5)) {
			request->delay += (request->delay >> 1);
			radlog(L_INFO, "STR",
			       request->number, request->component, request->module);
		} else {
			RDEBUG2("STR",
				request->number);
		}
		tv_add(&request->when, request->delay);

		INSERT_EVENT(wait_for_child_to_die, request);
		return;
	}

	RDEBUG2("STR", request->number);
	remove_from_request_hash(request);

#ifdef WITH_PROXY
	if (request->proxy) {
		wait_for_proxy_id_to_expire(request);
		return;
	}
#endif

	ev_request_free(&request);
}