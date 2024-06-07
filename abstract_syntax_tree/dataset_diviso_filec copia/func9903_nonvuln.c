bgp_rx_end_mark(struct bgp_parse_state *s, u32 afi)
{
  struct bgp_proto *p = s->proto;
  struct bgp_channel *c = bgp_get_channel(p, afi);

  BGP_TRACE(D_PACKETS, "STR");

  if (!c)
    DISCARD(BAD_AFI, BGP_AFI(afi), BGP_SAFI(afi));

  if (c->load_state == BFS_LOADING)
    c->load_state = BFS_NONE;

  if (p->p.gr_recovery)
    channel_graceful_restart_unlock(&c->c);

  if (c->gr_active)
    bgp_graceful_restart_done(c);
}