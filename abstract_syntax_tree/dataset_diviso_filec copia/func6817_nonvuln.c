  bool ms_can_fast_dispatch(const Message *m) {
    for (list<Dispatcher*>::iterator p = fast_dispatchers.begin();
	 p != fast_dispatchers.end();
	 ++p) {
      if ((*p)->ms_can_fast_dispatch(m))
	return true;
    }
    return false;
  }