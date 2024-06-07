bgp_write_packet (struct peer *peer)
{
  afi_t afi;
  safi_t safi;
  struct stream *s = NULL;
  struct bgp_advertise *adv;

  s = stream_fifo_head (peer->obuf);
  if (s)
    return s;

  for (afi = AFI_IP; afi < AFI_MAX; afi++)
    for (safi = SAFI_UNICAST; safi < SAFI_MAX; safi++)
      {
	adv = FIFO_HEAD (&peer->sync[afi][safi]->withdraw);
	if (adv)
	  {
	    s = bgp_withdraw_packet (peer, afi, safi);
	    if (s)
	      return s;
	  }
      }
    
  for (afi = AFI_IP; afi < AFI_MAX; afi++)
    for (safi = SAFI_UNICAST; safi < SAFI_MAX; safi++)
      {
	adv = FIFO_HEAD (&peer->sync[afi][safi]->update);
	if (adv)
	  {
            if (adv->binfo && adv->binfo->uptime < peer->synctime)
	      {
		if (CHECK_FLAG (adv->binfo->peer->cap, PEER_CAP_RESTART_RCV)
		    && CHECK_FLAG (adv->binfo->peer->cap, PEER_CAP_RESTART_ADV)
		    && ! CHECK_FLAG (adv->binfo->flags, BGP_INFO_STALE)
		    && safi != SAFI_MPLS_VPN)
		  {
		    if (CHECK_FLAG (adv->binfo->peer->af_sflags[afi][safi],
			PEER_STATUS_EOR_RECEIVED))
		      s = bgp_update_packet (peer, afi, safi);
		  }
		else
		  s = bgp_update_packet (peer, afi, safi);
	      }

	    if (s)
	      return s;
	  }

	if (CHECK_FLAG (peer->cap, PEER_CAP_RESTART_RCV))
	  {
	    if (peer->afc_nego[afi][safi] && peer->synctime
		&& ! CHECK_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_EOR_SEND)
		&& safi != SAFI_MPLS_VPN)
	      {
		SET_FLAG (peer->af_sflags[afi][safi], PEER_STATUS_EOR_SEND);
		return bgp_update_packet_eor (peer, afi, safi);
	      }
	  }
      }

  return NULL;
}