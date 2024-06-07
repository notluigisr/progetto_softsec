void OSD::handle_pg_scrub(MOSDScrub *m, PG *pg)
{
  pg->lock();
  if (pg->is_primary()) {
    pg->unreg_next_scrub();
    pg->scrubber.must_scrub = true;
    pg->scrubber.must_deep_scrub = m->deep || m->repair;
    pg->scrubber.must_repair = m->repair;
    pg->reg_next_scrub();
    dout(10) << "STR" << dendl;
  }
  pg->unlock();
}