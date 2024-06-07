  bool ms_deliver_verify_authorizer(Connection *con, int peer_type,
				    int protocol, bufferlist& authorizer, bufferlist& authorizer_reply,
				    bool& isvalid, CryptoKey& session_key) {
    for (list<Dispatcher*>::iterator p = dispatchers.begin();
	 p != dispatchers.end();
	 ++p) {
      if ((*p)->ms_verify_authorizer(con, peer_type, protocol, authorizer, authorizer_reply, isvalid, session_key))
	return true;
    }
    return false;
  }