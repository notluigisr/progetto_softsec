bool remove_dir(
  CephContext *cct,
  ObjectStore *store, SnapMapper *mapper,
  OSDriver *osdriver,
  ObjectStore::Sequencer *osr,
  coll_t coll, DeletingStateRef dstate,
  bool *finished,
  ThreadPool::TPHandle &handle)
{
  vector<ghobject_t> olist;
  int64_t num = 0;
  ObjectStore::Transaction t;
  ghobject_t next;
  handle.reset_tp_timeout();
  store->collection_list(
    coll,
    next,
    ghobject_t::get_max(),
    store->get_ideal_list_max(),
    &olist,
    &next);
  generic_dout(10) << __func__ << "STR" << olist << dendl;
  
  
  bool cont = true;
  for (vector<ghobject_t>::iterator i = olist.begin();
       i != olist.end();
       ++i) {
    if (i->is_pgmeta())
      continue;
    OSDriver::OSTransaction _t(osdriver->get_transaction(&t));
    int r = mapper->remove_oid(i->hobj, &_t);
    if (r != 0 && r != -ENOENT) {
      ceph_abort();
    }
    t.remove(coll, *i);
    if (++num >= cct->_conf->osd_target_transaction_size) {
      C_SaferCond waiter;
      store->queue_transaction(osr, std::move(t), &waiter);
      cont = dstate->pause_clearing();
      handle.suspend_tp_timeout();
      waiter.wait();
      handle.reset_tp_timeout();
      if (cont)
        cont = dstate->resume_clearing();
      if (!cont)
	return false;
      t = ObjectStore::Transaction();
      num = 0;
    }
  }
  if (num) {
    C_SaferCond waiter;
    store->queue_transaction(osr, std::move(t), &waiter);
    cont = dstate->pause_clearing();
    handle.suspend_tp_timeout();
    waiter.wait();
    handle.reset_tp_timeout();
    if (cont)
      cont = dstate->resume_clearing();
  }
  
  *finished = next.is_max();
  return cont;
}