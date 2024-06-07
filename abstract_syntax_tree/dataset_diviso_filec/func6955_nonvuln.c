void OSDService::remove_pgid(spg_t pgid, PG *pg)
{
  Mutex::Locker l(pgid_lock);
  assert(pgid_tracker.count(pgid));
  assert(pgid_tracker[pgid] > 0);
  pgid_tracker[pgid]--;
  if (pgid_tracker[pgid] == 0) {
    pgid_tracker.erase(pgid);
    live_pgs.erase(pgid);
  }
}