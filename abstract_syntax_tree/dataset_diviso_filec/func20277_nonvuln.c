void OSD::note_up_osd(int peer)
{
  service.forget_peer_epoch(peer, osdmap->get_epoch() - 1);
  heartbeat_set_peers_need_update();
}