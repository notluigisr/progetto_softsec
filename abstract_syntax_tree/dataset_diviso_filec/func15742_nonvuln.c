static void remove_from_proxy_hash(REQUEST *request)
{
	
	if (!request->in_proxy_hash) return;

	
	PTHREAD_MUTEX_LOCK(&proxy_mutex);

	if (!request->in_proxy_hash) {
		PTHREAD_MUTEX_UNLOCK(&proxy_mutex);
		return;
	}

	fr_packet_list_yank(proxy_list, request->proxy);
	fr_packet_list_id_free(proxy_list, request->proxy);

	
	if (!request->proxy_reply &&
	    request->home_server &&
	    request->home_server->currently_outstanding) {
		request->home_server->currently_outstanding--;
	}

	
	request->in_proxy_hash = FALSE;

  	PTHREAD_MUTEX_UNLOCK(&proxy_mutex);
}