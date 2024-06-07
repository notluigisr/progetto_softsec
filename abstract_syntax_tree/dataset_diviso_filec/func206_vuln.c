bgp_attr_as4_path (struct peer *peer, bgp_size_t length,
		 struct attr *attr, u_char flag, u_char *startp,
		 struct aspath **as4_path)
{
  bgp_size_t total;

  total = length + (CHECK_FLAG (flag, BGP_ATTR_FLAG_EXTLEN) ? 4 : 3);

  
  if (bgp_attr_flag_invalid (peer, BGP_ATTR_AS4_PATH, flag))
      return bgp_attr_malformed (peer, BGP_ATTR_AS4_PATH, flag,
                                 BGP_NOTIFY_UPDATE_ATTR_FLAG_ERR,
                                 startp, total);
  
  *as4_path = aspath_parse (peer->ibuf, length, 1);

  
  if (!*as4_path)
    {
      zlog (peer->log, LOG_ERR,
            "STR",
            peer->host, length);
      return bgp_attr_malformed (peer, BGP_ATTR_AS4_PATH, flag,
                                 BGP_NOTIFY_UPDATE_MAL_AS_PATH,
                                 NULL, 0);
    }

  
  if (as4_path)
    attr->flag |= ATTR_FLAG_BIT (BGP_ATTR_AS4_PATH);

  return BGP_ATTR_PARSE_PROCEED;
}