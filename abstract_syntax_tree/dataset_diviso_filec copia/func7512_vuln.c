bgp_attr_local_pref (struct peer *peer, bgp_size_t length, 
		     struct attr *attr, u_char flag, u_char *startp)
{
  bgp_size_t total;

  total = length + (CHECK_FLAG (flag, BGP_ATTR_FLAG_EXTLEN) ? 4 : 3);
  
  if (bgp_attr_flag_invalid (peer, BGP_ATTR_LOCAL_PREF, flag))
    return bgp_attr_malformed (peer, BGP_ATTR_LOCAL_PREF, flag,
                               BGP_NOTIFY_UPDATE_ATTR_FLAG_ERR,
                               startp, total);
  
  
  if (length != 4)
  {
    zlog (peer->log, LOG_ERR, "STR", length);
    return bgp_attr_malformed (peer, BGP_ATTR_LOCAL_PREF, flag,
                               BGP_NOTIFY_UPDATE_ATTR_LENG_ERR,
                               startp, total);
  }

  
  if (peer_sort (peer) == BGP_PEER_EBGP)
    {
      stream_forward_getp (peer->ibuf, length);
      return BGP_ATTR_PARSE_PROCEED;
    }

  attr->local_pref = stream_getl (peer->ibuf);

  
  attr->flag |= ATTR_FLAG_BIT (BGP_ATTR_LOCAL_PREF);

  return BGP_ATTR_PARSE_PROCEED;
}