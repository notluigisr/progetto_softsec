bgp_attr_aspath_check (struct peer *peer, struct attr *attr, u_char flag)
{
  
  struct bgp *bgp = peer->bgp;
  struct aspath *aspath;

  bgp = peer->bgp;
    
  
  if ((peer_sort (peer) == BGP_PEER_CONFED && ! aspath_left_confed_check (attr->aspath)) ||
     (peer_sort (peer) == BGP_PEER_EBGP && aspath_confed_check (attr->aspath)))
    {
      zlog (peer->log, LOG_ERR, "STR", peer->host);
      return bgp_attr_malformed (peer, BGP_ATTR_AS_PATH, flag,
                                 BGP_NOTIFY_UPDATE_MAL_AS_PATH,
                                 NULL, 0);
    }

  
  if (bgp != NULL && bgp_flag_check (bgp, BGP_FLAG_ENFORCE_FIRST_AS))
    {
      if (peer_sort (peer) == BGP_PEER_EBGP 
	  && ! aspath_firstas_check (attr->aspath, peer->as))
 	{
 	  zlog (peer->log, LOG_ERR,
 		"STR", peer->host, peer->as);
          return bgp_attr_malformed (peer, BGP_ATTR_AS_PATH, flag,
                                     BGP_NOTIFY_UPDATE_MAL_AS_PATH,
                                     NULL, 0);
 	}
    }

  
  if (peer->change_local_as &&
      ! CHECK_FLAG (peer->flags, PEER_FLAG_LOCAL_AS_NO_PREPEND))
    {
      aspath = aspath_dup (attr->aspath);
      aspath = aspath_add_seq (aspath, peer->change_local_as);
      aspath_unintern (&attr->aspath);
      attr->aspath = aspath_intern (aspath);
    }

  return BGP_ATTR_PARSE_PROCEED;
}