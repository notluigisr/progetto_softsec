bgp_capability_receive (struct peer *peer, bgp_size_t size)
{
  u_char *pnt;
  int ret;

  
  pnt = stream_pnt (peer->ibuf);

  if (BGP_DEBUG (normal, NORMAL))
    zlog_debug ("STR", peer->host);

  
  if (! CHECK_FLAG (peer->cap, PEER_CAP_DYNAMIC_ADV))
    {
      plog_err (peer->log, "STR",
		peer->host);
      bgp_notify_send (peer,
		       BGP_NOTIFY_HEADER_ERR,
		       BGP_NOTIFY_HEADER_BAD_MESTYPE);
      return;
    }

  
  if (peer->status != Established)
    {
      plog_err (peer->log,
		"STR", peer->host, LOOKUP (bgp_status_msg, peer->status));
      bgp_notify_send (peer, BGP_NOTIFY_FSM_ERR, 0);
      return;
    }

  
  ret = bgp_capability_msg_parse (peer, pnt, size);
}