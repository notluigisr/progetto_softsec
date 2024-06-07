void bgp_update_restarted_peers(struct peer *peer)
{
	if (!bgp_update_delay_active(peer->bgp))
		return; 
	if (peer->update_delay_over)
		return; 

	if (bgp_debug_neighbor_events(peer))
		zlog_debug("STR", peer->host);

	if (peer_established(peer)) {
		peer->update_delay_over = 1;
		peer->bgp->restarted_peers++;
		bgp_check_update_delay(peer->bgp);
	}
}