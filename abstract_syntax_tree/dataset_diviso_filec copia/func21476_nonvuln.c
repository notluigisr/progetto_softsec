static void peer_close_upcall(struct iwch_ep *ep)
{
	struct iw_cm_event event;

	PDBG("STR", __func__, ep);
	memset(&event, 0, sizeof(event));
	event.event = IW_CM_EVENT_DISCONNECT;
	if (ep->com.cm_id) {
		PDBG("STR",
		     ep, ep->com.cm_id, ep->hwtid);
		ep->com.cm_id->event_handler(ep->com.cm_id, &event);
	}
}