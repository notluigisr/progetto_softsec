  ConnectionRef _get_random_connection() {
    while (dispatcher.get_pending() > max_in_flight) {
      lock.Unlock();
      usleep(500);
      lock.Lock();
    }
    assert(lock.is_locked());
    boost::uniform_int<> choose(0, available_connections.size() - 1);
    int index = choose(rng);
    map<ConnectionRef, pair<Messenger*, Messenger*> >::iterator i = available_connections.begin();
    for (; index > 0; --index, ++i) ;
    return i->first;
  }