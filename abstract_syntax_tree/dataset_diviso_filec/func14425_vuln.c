bool Monitor::ms_verify_authorizer(Connection *con, int peer_type,
				   int protocol, bufferlist& authorizer_data,
				   bufferlist& authorizer_reply,
				   bool& isvalid, CryptoKey& session_key)
{
  dout(10) << "STR" << con->get_peer_addr()
	   << "STR" << ceph_entity_type_name(peer_type)
	   << "STR" << protocol << dendl;

  if (is_shutdown())
    return false;

  if (peer_type == CEPH_ENTITY_TYPE_MON &&
      auth_cluster_required.is_supported_auth(CEPH_AUTH_CEPHX)) {
    
    isvalid = false;
    if (protocol == CEPH_AUTH_CEPHX) {
      bufferlist::iterator iter = authorizer_data.begin();
      CephXServiceTicketInfo auth_ticket_info;
      
      if (authorizer_data.length()) {
	bool ret = cephx_verify_authorizer(g_ceph_context, &keyring, iter,
					  auth_ticket_info, authorizer_reply);
	if (ret) {
	  session_key = auth_ticket_info.session_key;
	  isvalid = true;
	} else {
	  dout(0) << "STR" << con->get_peer_addr() << dendl;
        }
      }
    } else {
      dout(0) << "STR" << dendl;
    }
  } else {
    
    isvalid = true;
  }
  return true;
}