void OSD::RemoveWQ::_process(
  pair<PGRef, DeletingStateRef> item,
  ThreadPool::TPHandle &handle)
{
  FUNCTRACE();
  PGRef pg(item.first);
  SnapMapper &mapper = pg->snap_mapper;
  OSDriver &driver = pg->osdriver;
  coll_t coll = coll_t(pg->info.pgid);
  pg->osr->flush();
  bool finished = false;

  if (!item.second->start_or_resume_clearing())
    return;

  bool cont = remove_dir(
    pg->cct, store, &mapper, &driver, pg->osr.get(), coll, item.second,
    &finished, handle);
  if (!cont)
    return;
  if (!finished) {
    if (item.second->pause_clearing())
      queue_front(item);
    return;
  }

  if (!item.second->start_deleting())
    return;

  ObjectStore::Transaction t;
  PGLog::clear_info_log(pg->info.pgid, &t);

  if (cct->_conf->osd_inject_failure_on_pg_removal) {
    generic_derr << "STR" << dendl;
    _exit(1);
  }
  t.remove_collection(coll);

  
  store->queue_transaction(
    pg->osr.get(),
    std::move(t),
    0, 
    0, 
    0, 
    new ContainerContext<PGRef>(pg),
    TrackedOpRef());

  item.second->finish_deleting();
}