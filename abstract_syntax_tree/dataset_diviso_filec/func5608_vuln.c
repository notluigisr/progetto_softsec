void ConnectionHandlerImpl::ActiveTcpSocket::newConnection() {
  
  ActiveTcpListenerOptRef new_listener;

  if (hand_off_restored_destination_connections_ && socket_->localAddressRestored()) {
    
    new_listener = listener_.parent_.findActiveTcpListenerByAddress(*socket_->localAddress());
  }
  if (new_listener.has_value()) {
    
    
    
    
    
    
    
    listener_.decNumConnections();
    new_listener.value().get().incNumConnections();
    new_listener.value().get().onAcceptWorker(std::move(socket_), false, true);
  } else {
    
    if (socket_->detectedTransportProtocol().empty()) {
      socket_->setDetectedTransportProtocol(
          Extensions::TransportSockets::TransportProtocolNames::get().RawBuffer);
    }
    
    listener_.newConnection(std::move(socket_));
  }
}