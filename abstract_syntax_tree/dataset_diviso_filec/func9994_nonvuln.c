void OSD::reset_heartbeat_peers()
{
  assert(osd_lock.is_locked());
  dout(10) << "STR" << dendl;
  Mutex::Locker l(heartbeat_lock);
  while (!heartbeat_peers.empty()) {
    HeartbeatInfo& hi = heartbeat_peers.begin()->second;
    hi.con_back->mark_down();
    if (hi.con_front) {
      hi.con_front->mark_down();
    }
    heartbeat_peers.erase(heartbeat_peers.begin());
  }
  failure_queue.clear();
}