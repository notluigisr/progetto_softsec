void Monitor::sync_force(Formatter *f, ostream& ss)
{
  bool free_formatter = false;

  if (!f) {
    
    f = new JSONFormatter();
    free_formatter = true;
  }

  auto tx(std::make_shared<MonitorDBStore::Transaction>());
  sync_stash_critical_state(tx);
  tx->put("STR", 1);
  store->apply_transaction(tx);

  f->open_object_section("STR");
  f->dump_int("STR", 0);
  f->dump_stream("STR";
  f->close_section(); 
  f->flush(ss);
  if (free_formatter)
    delete f;
}