forward_callback(isc_task_t *task, isc_event_t *event) {
	const char me[] = "STR";
	dns_requestevent_t *revent = (dns_requestevent_t *)event;
	dns_message_t *msg = NULL;
	char master[ISC_SOCKADDR_FORMATSIZE];
	isc_result_t result;
	dns_forward_t *forward;
	dns_zone_t *zone;

	UNUSED(task);

	forward = revent->ev_arg;
	INSIST(DNS_FORWARD_VALID(forward));
	zone = forward->zone;
	INSIST(DNS_ZONE_VALID(zone));

	ENTER;

	isc_sockaddr_format(&forward->addr, master, sizeof(master));

	if (revent->result != ISC_R_SUCCESS) {
		dns_zone_log(zone, ISC_LOG_INFO,
			     "STR",
			     master, dns_result_totext(revent->result));
		goto next_master;
	}

	result = dns_message_create(zone->mctx, DNS_MESSAGE_INTENTPARSE, &msg);
	if (result != ISC_R_SUCCESS)
		goto next_master;

	result = dns_request_getresponse(revent->request, msg,
					 DNS_MESSAGEPARSE_PRESERVEORDER |
					 DNS_MESSAGEPARSE_CLONEBUFFER);
	if (result != ISC_R_SUCCESS)
		goto next_master;

	switch (msg->rcode) {
	
	case dns_rcode_noerror:
	case dns_rcode_yxdomain:
	case dns_rcode_yxrrset:
	case dns_rcode_nxrrset:
	case dns_rcode_refused:
	case dns_rcode_nxdomain: {
		char rcode[128];
		isc_buffer_t rb;

		isc_buffer_init(&rb, rcode, sizeof(rcode));
		(void)dns_rcode_totext(msg->rcode, &rb);
		dns_zone_log(zone, ISC_LOG_INFO,
			     "STR"
			     "STR",
			     master, (int)rb.used, rcode);
		break;
	}

	
	case dns_rcode_notzone:
	case dns_rcode_notauth: {
		char rcode[128];
		isc_buffer_t rb;

		isc_buffer_init(&rb, rcode, sizeof(rcode));
		(void)dns_rcode_totext(msg->rcode, &rb);
		dns_zone_log(zone, ISC_LOG_WARNING,
			     "STR"
			     "STR",
			     master, (int)rb.used, rcode);
		goto next_master;
	}

	
	case dns_rcode_formerr:
	case dns_rcode_servfail:
	case dns_rcode_notimp:
	case dns_rcode_badvers:
	default:
		goto next_master;
	}

	
	(forward->callback)(forward->callback_arg, ISC_R_SUCCESS, msg);
	msg = NULL;
	dns_request_destroy(&forward->request);
	forward_destroy(forward);
	isc_event_free(&event);
	return;

 next_master:
	if (msg != NULL)
		dns_message_destroy(&msg);
	isc_event_free(&event);
	forward->which++;
	dns_request_destroy(&forward->request);
	result = sendtomaster(forward);
	if (result != ISC_R_SUCCESS) {
		
		dns_zone_log(zone, ISC_LOG_DEBUG(3),
			     "STR");
		(forward->callback)(forward->callback_arg, result, NULL);
		forward_destroy(forward);
	}
}