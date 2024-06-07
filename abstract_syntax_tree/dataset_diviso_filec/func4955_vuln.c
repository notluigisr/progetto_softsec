bgp_attr_cluster_list (struct peer *peer, bgp_size_t length, 
		       struct attr *attr, u_char flag, u_char *startp)
{
  bgp_size_t total;

  total = length + (CHECK_FLAG (flag, BGP_ATTR_FLAG_EXTLEN) ? 4 : 3);
  
  if (bgp_attr_flag_invalid (peer, BGP_ATTR_CLUSTER_LIST, flag))
    return bgp_attr_malformed (peer, BGP_ATTR_CLUSTER_LIST, flag,
                               BGP_NOTIFY_UPDATE_ATTR_FLAG_ERR,
                               startp, total);
  
  if (length % 4)
    {
      zlog (peer->log, LOG_ERR, "STR", length);

      return bgp_attr_malformed (peer, BGP_ATTR_CLUSTER_LIST, flag,
                                 BGP_NOTIFY_UPDATE_ATTR_LENG_ERR,
                                 startp, total);
    }

  (bgp_attr_extra_get (attr))->cluster 
    = cluster_parse ((struct in_addr *)stream_pnt (peer->ibuf), length);
  
  
  stream_forward_getp (peer->ibuf, length);

  attr->flag |= ATTR_FLAG_BIT (BGP_ATTR_CLUSTER_LIST);

  return BGP_ATTR_PARSE_PROCEED;
}