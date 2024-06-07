void Monitor::no_reply(MonOpRequestRef op)
{
  MonSession *session = op->get_session();
  Message *req = op->get_req();

  if (session->proxy_con) {
    dout(10) << "STR" << req->get_source_inst()
	     << "STR" << session->proxy_con->get_peer_addr()
	     << "STR" << *req << dendl;
    session->proxy_con->send_message(new MRoute(session->proxy_tid, NULL));
    op->mark_event("STR");
  } else {
    dout(10) << "STR" << req->get_source_inst()
             << "STR" << *req << dendl;
    op->mark_event("STR");
  }
}