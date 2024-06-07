bgp_default_update_send (struct peer *peer, struct attr *attr,
			 afi_t afi, safi_t safi, struct peer *from)
{
  struct stream *s;
  struct stream *packet;
  struct prefix p;
  unsigned long pos;
  bgp_size_t total_attr_len;
  char attrstr[BUFSIZ];
  char buf[BUFSIZ];

#ifdef DISABLE_BGP_ANNOUNCE
  return;
#endif 

  if (afi == AFI_IP)
    str2prefix ("STR", &p);
#ifdef HAVE_IPV6
  else 
    str2prefix ("STR", &p);
#endif 

  
  if (BGP_DEBUG (update, UPDATE_OUT))
    {
      bgp_dump_attr (peer, attr, attrstr, BUFSIZ);
      zlog (peer->log, LOG_DEBUG, "STR",
	    peer->host, inet_ntop(p.family, &(p.u.prefix), buf, BUFSIZ),
	    p.prefixlen, attrstr);
    }

  s = stream_new (BGP_MAX_PACKET_SIZE);

  
  bgp_packet_set_marker (s, BGP_MSG_UPDATE);

  
  stream_putw (s, 0);

  
  pos = stream_get_endp (s);
  stream_putw (s, 0);
  total_attr_len = bgp_packet_attribute (NULL, peer, s, attr, &p, afi, safi, from, NULL, NULL);

  
  stream_putw_at (s, pos, total_attr_len);

  
  if (p.family == AF_INET && safi == SAFI_UNICAST)
    stream_put_prefix (s, &p);

  
  bgp_packet_set_size (s);

  packet = stream_dup (s);
  stream_free (s);

  
#ifdef DEBUG
  
#endif 

  
  bgp_packet_add (peer, packet);

  BGP_WRITE_ON (peer->t_write, bgp_write, peer->fd);
}