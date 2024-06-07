bgp_attr_origin (struct peer *peer, bgp_size_t length, 
		 struct attr *attr, u_char flag, u_char *startp)
{
  bgp_size_t total;

  
  total = length + (CHECK_FLAG (flag, BGP_ATTR_FLAG_EXTLEN) ? 4 : 3);

  
  if (bgp_attr_flag_invalid (peer, BGP_ATTR_ORIGIN, flag))
    return bgp_attr_malformed (peer, BGP_ATTR_ORIGIN, flag,
                               BGP_NOTIFY_UPDATE_ATTR_FLAG_ERR,
                               startp, total);

  
  if (length != 1)
    {
      zlog (peer->log, LOG_ERR, "STR",
	    length);
      return bgp_attr_malformed (peer, BGP_ATTR_ORIGIN, flag,
                                 BGP_NOTIFY_UPDATE_ATTR_LENG_ERR,
                                 startp, total);
    }

  
  attr->origin = stream_getc (BGP_INPUT (peer));

  
  if ((attr->origin != BGP_ORIGIN_IGP)
      && (attr->origin != BGP_ORIGIN_EGP)
      && (attr->origin != BGP_ORIGIN_INCOMPLETE))
    {
      zlog (peer->log, LOG_ERR, "STR",
	      attr->origin);
      return bgp_attr_malformed (peer, BGP_ATTR_ORIGIN, flag,
                                 BGP_NOTIFY_UPDATE_INVAL_ORIGIN,
                                 startp, total);
    }

  
  attr->flag |= ATTR_FLAG_BIT (BGP_ATTR_ORIGIN);

  return 0;
}