  void handle_reset(Connection *con) {
    Mutex::Locker l(lock);
    available_connections.erase(con);
    dispatcher.clear_pending(con);
  }