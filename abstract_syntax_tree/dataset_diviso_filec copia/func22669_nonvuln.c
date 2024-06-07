bgp_default_withdraw_send (struct peer *peer, afi_t afi, safi_t safi)
{
  struct stream *s;
  struct stream *packet;
  struct prefix p;
  unsigned long pos;
  unsigned long cp;
  bgp_size_t unfeasible_len;
  bgp_size_t total_attr_len;
  char buf[BUFSIZ];

  if (DISABLE_BGP_ANNOUNCE)
    return;

  if (afi == AFI_IP)
    str2prefix ("STR", &p);
#ifdef HAVE_IPV6
  else 
    str2prefix ("STR", &p);
#endif 

  total_attr_len = 0;
  pos = 0;

  if (BGP_DEBUG (update, UPDATE_OUT))
    zlog (peer->log, LOG_DEBUG, "STR",
          peer->host, inet_ntop(p.family, &(p.u.prefix), buf, BUFSIZ),
          p.prefixlen);

  s = stream_new (BGP_MAX_PACKET_SIZE);

  
  bgp_packet_set_marker (s, BGP_MSG_UPDATE);

  ;
  cp = stream_get_endp (s);
  stream_putw (s, 0);

  
  if (p.family == AF_INET && safi == SAFI_UNICAST)
    {
      stream_put_prefix (s, &p);

      unfeasible_len = stream_get_endp (s) - cp - 2;

      
      stream_putw_at (s, cp, unfeasible_len);

      
      stream_putw (s, 0);
    }
  else
    {
      pos = stream_get_endp (s);
      stream_putw (s, 0);
      total_attr_len = bgp_packet_withdraw (peer, s, &p, afi, safi, NULL, NULL);

      
      stream_putw_at (s, pos, total_attr_len);
    }

  bgp_packet_set_size (s);

  packet = stream_dup (s);
  stream_free (s);

  
  bgp_packet_add (peer, packet);

  BGP_WRITE_ON (peer->t_write, bgp_write, peer->fd);
}