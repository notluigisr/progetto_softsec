bool MDSDaemon::ms_handle_reset(Connection *con)
{
  if (con->get_peer_type() != CEPH_ENTITY_TYPE_CLIENT)
    return false;

  Mutex::Locker l(mds_lock);
  if (stopping) {
    return false;
  }
  dout(5) << "STR" << con->get_peer_addr() << dendl;
  if (beacon.get_want_state() == CEPH_MDS_STATE_DNE)
    return false;

  Session *session = static_cast<Session *>(con->get_priv());
  if (session) {
    if (session->is_closed()) {
      dout(3) << "STR" << session->info.inst << dendl;
      con->mark_down();
      con->set_priv(NULL);
    }
    session->put();
  } else {
    con->mark_down();
  }
  return false;
}