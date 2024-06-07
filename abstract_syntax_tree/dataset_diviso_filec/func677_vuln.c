CodecClient::CodecClient(Type type, Network::ClientConnectionPtr&& connection,
                         Upstream::HostDescriptionConstSharedPtr host,
                         Event::Dispatcher& dispatcher)
    : type_(type), connection_(std::move(connection)), host_(host),
      idle_timeout_(host_->cluster().idleTimeout()) {
  if (type_ != Type::HTTP3) {
    
    
    
    connection_->detectEarlyCloseWhenReadDisabled(false);
  }
  connection_->addConnectionCallbacks(*this);
  connection_->addReadFilter(Network::ReadFilterSharedPtr{new CodecReadFilter(*this)});

  ENVOY_CONN_LOG(debug, "STR", *connection_);
  connection_->connect();

  if (idle_timeout_) {
    idle_timer_ = dispatcher.createTimer([this]() -> void { onIdleTimeout(); });
    enableIdleTimer();
  }

  
  
  connection_->noDelay(true);
}