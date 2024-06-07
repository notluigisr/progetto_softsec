void ConnectionManagerImpl::doDeferredStreamDestroy(ActiveStream& stream) {
  if (stream.max_stream_duration_timer_) {
    stream.max_stream_duration_timer_->disableTimer();
    stream.max_stream_duration_timer_ = nullptr;
  }
  if (stream.stream_idle_timer_ != nullptr) {
    stream.stream_idle_timer_->disableTimer();
    stream.stream_idle_timer_ = nullptr;
  }
  stream.filter_manager_.disarmRequestTimeout();
  if (stream.request_header_timer_ != nullptr) {
    stream.request_header_timer_->disableTimer();
    stream.request_header_timer_ = nullptr;
  }

  stream.completeRequest();
  stream.filter_manager_.onStreamComplete();
  stream.filter_manager_.log();

  stream.filter_manager_.destroyFilters();

  read_callbacks_->connection().dispatcher().deferredDelete(stream.removeFromList(streams_));

  if (connection_idle_timer_ && streams_.empty()) {
    connection_idle_timer_->enableTimer(config_.idleTimeout().value());
  }
}