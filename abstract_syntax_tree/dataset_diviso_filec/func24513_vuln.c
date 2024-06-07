bgp_attr_nexthop (struct peer *peer, bgp_size_t length, 
		  struct attr *attr, u_char flag, u_char *startp)
{
  bgp_size_t total;
  in_addr_t nexthop_h, nexthop_n;

  total = length + (CHECK_FLAG (flag, BGP_ATTR_FLAG_EXTLEN) ? 4 : 3);

  
  if (bgp_attr_flag_invalid (peer, BGP_ATTR_NEXT_HOP, flag))
    return bgp_attr_malformed (peer, BGP_ATTR_NEXT_HOP, flag,
                               BGP_NOTIFY_UPDATE_ATTR_FLAG_ERR,
                               startp, total);

  
  if (length != 4)
    {
      zlog (peer->log, LOG_ERR, "STR",
	      length);

      return bgp_attr_malformed (peer, BGP_ATTR_NEXT_HOP, flag,
                                 BGP_NOTIFY_UPDATE_ATTR_LENG_ERR,
                                 startp, total);
    }

  
  nexthop_n = stream_get_ipv4 (peer->ibuf);
  nexthop_h = ntohl (nexthop_n);
  if (IPV4_NET0 (nexthop_h) || IPV4_NET127 (nexthop_h) || IPV4_CLASS_DE (nexthop_h))
    {
      char buf[INET_ADDRSTRLEN];
      inet_ntop (AF_INET, &nexthop_h, buf, INET_ADDRSTRLEN);
      zlog (peer->log, LOG_ERR, "STR", buf);
      return bgp_attr_malformed (peer, BGP_ATTR_NEXT_HOP, flag,
                                 BGP_NOTIFY_UPDATE_INVAL_NEXT_HOP,
                                 startp, total);
    }

  attr->nexthop.s_addr = nexthop_n;
  attr->flag |= ATTR_FLAG_BIT (BGP_ATTR_NEXT_HOP);

  return BGP_ATTR_PARSE_PROCEED;
}