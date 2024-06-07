void ConnectionHandlerImpl::ActiveTcpListener::newConnection(
    Network::ConnectionSocketPtr&& socket) {
  
  const auto filter_chain = config_.filterChainManager().findFilterChain(*socket);
  if (filter_chain == nullptr) {
    ENVOY_LOG(debug, "STR");
    stats_.no_filter_chain_match_.inc();
    socket->close();
    return;
  }

  auto transport_socket = filter_chain->transportSocketFactory().createTransportSocket(nullptr);
  ActiveTcpConnectionPtr active_connection(new ActiveTcpConnection(
      *this,
      parent_.dispatcher_.createServerConnection(std::move(socket), std::move(transport_socket)),
      parent_.dispatcher_.timeSource()));
  active_connection->connection_->setBufferLimits(config_.perConnectionBufferLimitBytes());

  const bool empty_filter_chain = !config_.filterChainFactory().createNetworkFilterChain(
      *active_connection->connection_, filter_chain->networkFilterFactories());
  if (empty_filter_chain) {
    ENVOY_CONN_LOG(debug, "STR", *active_connection->connection_);
    active_connection->connection_->close(Network::ConnectionCloseType::NoFlush);
  }

  
  if (active_connection->connection_->state() != Network::Connection::State::Closed) {
    ENVOY_CONN_LOG(debug, "STR", *active_connection->connection_);
    active_connection->connection_->addConnectionCallbacks(*active_connection);
    active_connection->moveIntoList(std::move(active_connection), connections_);
  }
}