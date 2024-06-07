bgp_attr_malformed (struct peer *peer, u_char type, u_char flag,
                    u_char subcode, u_char *startp, bgp_size_t length)
{
  
  if (peer_sort (peer) != BGP_PEER_EBGP)
    {
      bgp_notify_send_with_data (peer, BGP_NOTIFY_UPDATE_ERR, subcode,
                                 startp, length);
      return BGP_ATTR_PARSE_ERROR;

    }
  
  switch (type) {
    
    case BGP_ATTR_AS4_AGGREGATOR:
    case BGP_ATTR_AGGREGATOR:
    case BGP_ATTR_ATOMIC_AGGREGATE:
      return BGP_ATTR_PARSE_PROCEED;
    
    
    case BGP_ATTR_ORIGIN:
    case BGP_ATTR_AS_PATH:
    case BGP_ATTR_NEXT_HOP:
    case BGP_ATTR_MULTI_EXIT_DISC:
    case BGP_ATTR_LOCAL_PREF:
    case BGP_ATTR_COMMUNITIES:
    case BGP_ATTR_ORIGINATOR_ID:
    case BGP_ATTR_CLUSTER_LIST:
    case BGP_ATTR_MP_REACH_NLRI:
    case BGP_ATTR_MP_UNREACH_NLRI:
    case BGP_ATTR_EXT_COMMUNITIES:
      bgp_notify_send_with_data (peer, BGP_NOTIFY_UPDATE_ERR, subcode,
                                 startp, length);
      return BGP_ATTR_PARSE_ERROR;
  }
  
  
  if (CHECK_FLAG (flag, BGP_ATTR_FLAG_TRANS)
      && CHECK_FLAG (flag, BGP_ATTR_FLAG_OPTIONAL)
      && CHECK_FLAG (flag, BGP_ATTR_FLAG_PARTIAL))
    return BGP_ATTR_PARSE_WITHDRAW;
  
  
  return BGP_ATTR_PARSE_ERROR;
}