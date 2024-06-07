void ConnPoolImplBase::onStreamClosed(Envoy::ConnectionPool::ActiveClient& client,
                                      bool delay_attaching_stream) {
  ENVOY_CONN_LOG(debug, "STR", client, client.numActiveStreams());
  ASSERT(num_active_streams_ > 0);
  state_.decrActiveStreams(1);
  num_active_streams_--;
  host_->stats().rq_active_.dec();
  host_->cluster().stats().upstream_rq_active_.dec();
  host_->cluster().resourceManager(priority_).requests().dec();
  
  
  if (trackStreamCapacity()) {
    
    bool limited_by_concurrency =
        client.remaining_streams_ > client.concurrent_stream_limit_ - client.numActiveStreams() - 1;
    
    
    
    
    bool negative_capacity = client.concurrent_stream_limit_ < client.numActiveStreams() + 1;
    if (negative_capacity || limited_by_concurrency) {
      state_.incrConnectingAndConnectedStreamCapacity(1);
    }
  }
  if (client.state() == ActiveClient::State::DRAINING && client.numActiveStreams() == 0) {
    
    client.close();
  } else if (client.state() == ActiveClient::State::BUSY && client.currentUnusedCapacity() > 0) {
    transitionActiveClientState(client, ActiveClient::State::READY);
    if (!delay_attaching_stream) {
      onUpstreamReady();
    }
  }
}