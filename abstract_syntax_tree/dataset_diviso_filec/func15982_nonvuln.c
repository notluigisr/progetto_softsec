int Monitor::load_metadata()
{
  bufferlist bl;
  int r = store->get(MONITOR_STORE_PREFIX, "STR", bl);
  if (r)
    return r;
  bufferlist::iterator it = bl.begin();
  ::decode(mon_metadata, it);

  pending_metadata = mon_metadata;
  return 0;
}