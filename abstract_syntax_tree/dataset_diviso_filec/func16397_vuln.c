void ConnPoolImplBase::closeIdleConnectionsForDrainingPool() {
  
  std::list<ActiveClient*> to_close;

  for (auto& client : ready_clients_) {
    if (client->numActiveStreams() == 0) {
      to_close.push_back(client.get());
    }
  }

  if (pending_streams_.empty()) {
    for (auto& client : connecting_clients_) {
      to_close.push_back(client.get());
    }
  }

  for (auto& entry : to_close) {
    ENVOY_LOG_EVENT(debug, "STR",
                    entry->id(), host_->cluster().name());
    entry->close();
  }
}